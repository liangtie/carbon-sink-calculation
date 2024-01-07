#ifndef NETWORK_INTERACTION_H
#define NETWORK_INTERACTION_H

#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>

#include <QtNetwork/qnetworkaccessmanager.h>
#include <qobject.h>

#include <QtNetwork/QNetworkAccessManager>

#include "http_param.h"

class CarbonSinkForm;
using CarbonSinkFormPtr = std::shared_ptr<CarbonSinkForm>;

class NetworkInteraction : public QObject
{
    Q_OBJECT

  public:
    static NetworkInteraction& getInstance()
    {
        static NetworkInteraction ins;
        return ins;
    }

    enum RequestKind
    {
        LOGIN,
        ADD_USER,
        UPLOAD_RESULT,
        GET_RESULTS,
    };

    ~NetworkInteraction() override;

    void login(LoginForm const& form);

    void addUser(AddUserForm const& from);

    void uploadResult(ResultForm const& form);

    void startFetchResult();

    template<class T>
    QNetworkReply* sendRequest(T const& request, QString endPoint);

    [[nodiscard]] auto& getLoginResult() const { return _loginResponse; }

    auto& getResultFetched() const { return _resultsFetched; }

  signals:

    void AddUserSuccess(bool success);
    void LoginSuccess(int role);
    void resultReady();

  protected:
    NetworkInteraction();

    void processResponse(QNetworkReply* reply);

  private:
    QNetworkAccessManager* _netAccess;
    std::map<QNetworkReply*, RequestKind> _replies;
    LoginResponse _loginResponse;
    std::list<std::shared_ptr<CarbonSinkForm>> _resultsFetched;
};

#endif