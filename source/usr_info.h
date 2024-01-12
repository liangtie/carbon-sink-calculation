#ifndef USR_INFO_H
#define USR_INFO_H

#include <qstring.h>

#include "user_role.h"

struct UserInfo
{
    QString name;
    int id;
    UserRoles role;
};

#endif