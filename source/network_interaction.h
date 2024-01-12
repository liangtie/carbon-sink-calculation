#ifndef NETWORK_INTERACTION_H
#define NETWORK_INTERACTION_H

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <optional>

#include <QtNetwork/qnetworkaccessmanager.h>
#include <qobject.h>

#include <QtNetwork/QNetworkAccessManager>

#include "http_param.h"
#include "usr_info.h"

class CarbonSinkForm;
using CarbonSinkFormPtr = std::shared_ptr<CarbonSinkForm>;
using json = nlohmann::json;

enum RequestKind
{
    LOGIN,
    ADD_USER,
    UPLOAD_RESULT,
    GET_RESULTS,

    RM_USR,
    UPDATE_USR_PASSWORD,
    GET_ALL_USR
};
struct ChainedRequest
{
    RequestKind kind;
    std::optional<std::function<void(json)>> accept {};
    std::optional<std::function<void(json)>> reject {};
};

class NetworkInteraction : public QObject
{
    Q_OBJECT

  public:
    static NetworkInteraction& getInstance()
    {
        static NetworkInteraction ins;
        return ins;
    }

    ~NetworkInteraction() override;

    void login(LoginForm const& form);

    void addUser(AddUserForm const& from);

    void rmUser(int id);

    void getUserList(bool show_mgr = false);

    void updateUserPassword(UserInfo const& info);

    void uploadResult(ResultForm const& form);

    void startFetchResult();

    template<class T>
    QNetworkReply* sendRequest(T const& request, QString endPoint);

    [[nodiscard]] auto& getLoginResult() const { return _loginResponse; }

    auto& getResultFetched() const { return _resultsFetched; }

    auto& getUserInfo() const { return _user_info; }

  signals:

    void loginSuccess(int role);
    void resultReady();
    void getUsrInfSuccess(bool show_mgr);
    void usrInfoChanged();

  protected:
    NetworkInteraction();

    void processResponse(QNetworkReply* reply);

  private:
    QNetworkAccessManager* _netAccess;
    std::map<QNetworkReply*, ChainedRequest> _requests;
    LoginResponse _loginResponse;
    std::list<std::shared_ptr<CarbonSinkForm>> _resultsFetched;
    UserInfoList _user_info;
    bool _show_mgr {};
};

Q_DECLARE_METATYPE(std::list<std::shared_ptr<CarbonSinkForm>>);
#endif