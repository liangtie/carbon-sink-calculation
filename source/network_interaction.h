#ifndef NETWORK_INTERACTION_H
#define NETWORK_INTERACTION_H

#include <memory>
#include <string>

#include <QtNetwork/qnetworkaccessmanager.h>
#include <nlohmann/detail/macro_scope.hpp>
#include <nlohmann/json.hpp>

#include <QtNetwork/QNetworkAccessManager>

#include "http_param.h"



class NetworkInteraction
{
  public:
    NetworkInteraction();
    ~NetworkInteraction();

  private:
    std::unique_ptr<QNetworkAccessManager> _netAccess;
};

#endif