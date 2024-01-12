#ifndef USR_INFO_H
#define USR_INFO_H

#include <qstring.h>

#include "http_param.h"
struct UserInfo : AddUserForm
{
    int id {};
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        UserInfo, name, account, password, company, role, createTime, id)
};
using UserInfoList = std::vector<UserInfo>;
#endif