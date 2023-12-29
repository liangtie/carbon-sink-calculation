#include <memory>
#include "network_interaction.h"

NetworkInteraction::NetworkInteraction():_netAccess(std::make_unique<QNetworkAccessManager>())
{

}

NetworkInteraction::~NetworkInteraction()
{

}