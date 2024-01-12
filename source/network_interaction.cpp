#include <QApplication>
#include <QFile>
#include <QHttpPart>
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTextStream>
#include <exception>
#include <memory>
#include <set>
#include <string>
#include <utility>

#include "network_interaction.h"

#include <qmessagebox.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <qurl.h>

#include "carbon_sink_form.h"
#include "usr_info.h"

static constexpr auto url = "http://101.200.162.174:8088/";

struct ResponseBase
{
    std::string code;
    json data;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ResponseBase, code, data);
};

static const std::string SUCCESS = "200";

template<typename T>

auto toByteArray(T const& p)
{
    auto j = nlohmann::json(p).dump();
    return QByteArray::fromStdString(j);
}

template<class T>
QNetworkReply* NetworkInteraction::sendRequest(T const& form, QString endPoint)
{
    QNetworkRequest request((QUrl(QString(url) + endPoint)));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/json;charset=UTF-8");
    return _netAccess->post(request, toByteArray(form));
}

NetworkInteraction::NetworkInteraction()
    : _netAccess(new QNetworkAccessManager(this))
{
    connect(_netAccess,
            &QNetworkAccessManager::finished,
            this,
            &NetworkInteraction::processResponse);
}

void NetworkInteraction::processResponse(QNetworkReply* rep)
{
    QByteArray bts = rep->readAll();
    QString str(bts);

    try {
        auto j = json::parse(str.toStdString());
        ResponseBase b;
        j.get_to(b);
        const auto success = b.code == SUCCESS;
        if (auto loc = _requests.find(rep); loc != _requests.end()) {
            switch (loc->second.kind) {
                case LOGIN: {
                    if ((b.code == SUCCESS)) {
                        b.data.get_to(_loginResponse);
                        emit loginSuccess(std::stoi(_loginResponse.role));
                    } else {
                        QMessageBox::warning(
                            nullptr, "错误", "无效的账户或密码");
                    }

                } break;
                case UPLOAD_RESULT:
                    if ((b.code == SUCCESS)) {
                        //
                    } else {
                        QMessageBox::warning(
                            nullptr, "错误", "上传计算结果失败");
                    }
                    break;

                case GET_RESULTS: {
                    std::list<ResultForm> results;
                    b.data["records"].get_to(results);
                    for (const auto& r : results) {
                        auto ss = std::make_shared<CarbonSinkForm>();
                        ss->fromForm(r);
                        _resultsFetched.push_back(std::move(ss));
                    }

                    emit resultReady();
                    break;
                }
                case ADD_USER: {
                    if (success) {
                        QMessageBox::information(
                            nullptr, "提示", "新建用户成功");
                    } else {
                        QMessageBox::warning(nullptr, "提示", "新建用户失败");
                    }
                } break;
                case RM_USR: {
                    if (success) {
                    } else {
                        QMessageBox::warning(nullptr, "提示", "删除用户失败");
                    }
                    break;
                }
                case UPDATE_USR_PASSWORD: {
                    if (success) {
                        QMessageBox::information(
                            nullptr, "提示", "修改用户密码成功");
                    } else {
                        QMessageBox::warning(
                            nullptr, "提示", "修改用户密码失败");
                    }
                    break;
                }
                case GET_ALL_USR: {
                    b.data["records"].get_to(_user_info);
                    if (success) {
                        emit getUsrInfSuccess();
                    } else {
                        QMessageBox::warning(
                            nullptr, "提示", "获取用户信息失败");
                    }
                    break;
                }
            }
            static const auto kUserInfoChangeT = std::set<int> {
                ADD_USER, RM_USR, GET_ALL_USR, UPDATE_USR_PASSWORD};

            if (kUserInfoChangeT.find(loc->second.kind)
                != kUserInfoChangeT.end())
            {
                emit usrInfoChanged(_user_info);
            }

            _requests.erase(loc);
        }
    } catch (std::exception const& e) {
        QMessageBox::information(nullptr, "网络错误", e.what());
    }
    rep->deleteLater();
}

NetworkInteraction::~NetworkInteraction() = default;

void NetworkInteraction::login(LoginForm const& form)
{
    _requests.try_emplace(sendRequest(form, "user/login"),
                          ChainedRequest {LOGIN});
}

void NetworkInteraction::addUser(AddUserForm const& form)
{
    _requests.try_emplace(sendRequest(form, "user/insert"),
                          ChainedRequest {ADD_USER});
}

void NetworkInteraction::rmUser(int id)
{
    _requests.try_emplace(sendRequest(id, "user/delete"),
                          ChainedRequest {RM_USR});
}

void NetworkInteraction::getUserList()
{
    _requests.try_emplace(sendRequest("", "user/pageList"),
                          ChainedRequest {GET_ALL_USR});
}

void NetworkInteraction::updateUserPassword(UserInfo const& info)
{
    rmUser(info.id);
    _requests.try_emplace(sendRequest(info, "calculate/insert"),
                          ChainedRequest {UPDATE_USR_PASSWORD});
}

void NetworkInteraction::uploadResult(ResultForm const& form)
{
    _requests.try_emplace(sendRequest(form, "calculate/insert"),
                          ChainedRequest {UPLOAD_RESULT});
}

void NetworkInteraction::startFetchResult()
{
    if (_loginResponse.hasFetchResult) {
        emit resultReady();
        return;
    }

    GetResultsForm form;
    form.role = _loginResponse.role;
    form.userId = _loginResponse.id;
    _requests.try_emplace(sendRequest(form, "calculate/pageList"),
                          ChainedRequest {GET_RESULTS});
}
