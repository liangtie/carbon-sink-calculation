#include <QDateTime>

#include "utils.h"

auto Utils::getCurrentDateTime() -> std::string
{
    return QDateTime::currentDateTime()
        .toString("yyyy-MM-dd hh:mm:ss")
        .toStdString();
}
