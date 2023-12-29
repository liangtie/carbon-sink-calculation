#ifndef HTTP_PARAM_H
#define HTTP_PARAM_H

#include <string>

#include <nlohmann/json.hpp>

#include "utils.h"

struct AddUser
{
    std::string name;
    std::string account;
    std::string password;
    std::string company;
    int role = 3;
    std::string createTime = Utils::getCurrentDateTime();
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        AddUser, name, account, password, company, role, createTime)
};

struct ResultForm
{
    std::string province;
    std::string city;
    std::string county;
    std::string architecturalType;
    std::string cementType;
    std::string cementLevel;
    std::string concreteLevel;
    std::string structureType;

    std::string structureTime;
    std::string structureArea;
    std::string structureLine;
    std::string structureNum;

    std::string structureHigh;
    std::string structureCount;
    std::string calculateResult;
    std::string createTime;
    std::string userId;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ResultForm,
                                   province,
                                   city,
                                   architecturalType,
                                   cementType,
                                   cementLevel,
                                   concreteLevel,
                                   structureType,
                                   structureTime,
                                   structureArea,
                                   structureLine,
                                   structureNum,
                                   structureHigh,
                                   structureCount,
                                   calculateResult,
                                   createTime,
                                   userId,
                                   calculateResult)
};

struct Login
{
    std::string account;
    std::string password;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Login, account, password)
};

#endif