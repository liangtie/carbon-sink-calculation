#include <QApplication>
#include <QHttpPart>
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <cstddef>
#include <exception>
#include <memory>
#include <string>
#include <utility>
#include <QFile>
#include <QTextStream>

#include "network_interaction.h"

#include <qmessagebox.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <qurl.h>

#include "carbon_sink_form.h"

using json = nlohmann::json;

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
        if (auto loc = _replies.find(rep); loc != _replies.end()) {
            switch (loc->second) {
                case LOGIN: {
                    if ((b.code == SUCCESS)) {
                        b.data.get_to(_loginResponse);
                        emit LoginSuccess(std::stoi(_loginResponse.role));
                    } else {
                        QMessageBox::warning(
                            nullptr, "错误", "无效的账户或密码");
                    }

                } break;
                case ADD_USER: {
                    emit AddUserSuccess(b.code == SUCCESS);

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
            }
        }
    } catch (std::exception const& e) {
        QMessageBox::information(nullptr, "网络错误", e.what());
    }
    rep->deleteLater();
}

NetworkInteraction::~NetworkInteraction() = default;

void NetworkInteraction::login(LoginForm const& form)
{
    _replies.try_emplace(sendRequest(form, "user/login"), LOGIN);
}

void NetworkInteraction::addUser(AddUserForm const& form)
{
    _replies.try_emplace(sendRequest(form, "user/insert"), ADD_USER);
}

void NetworkInteraction::uploadResult(ResultForm const& form)
{
    _replies.try_emplace(sendRequest(form, "calculate/insert"), UPLOAD_RESULT);
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
    _replies.try_emplace(sendRequest(form, "calculate/pageList"), GET_RESULTS);
}
