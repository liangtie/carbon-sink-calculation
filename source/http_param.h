#ifndef HTTP_PARAM_H
#define HTTP_PARAM_H

#include <string>

#include <nlohmann/json.hpp>

#include "utils.h"

struct AddUserForm
{
    std::string name;
    std::string account;
    std::string password;
    std::string company;
    std::string role = "3";
    std::string createTime = Utils::getCurrentDateTime();
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        AddUserForm, name, account, password, company, role, createTime)
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
    int userId;

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

struct LoginForm
{
    std::string account;
    std::string password;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoginForm, account, password)
};

struct GetResultsForm
{
    int userId;
    std::string role;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetResultsForm, userId, role)
};

struct LoginResponse
{
    int id {};
    std::string name;
    std::string password;
    std::string role;
    bool hasFetchResult = false;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoginResponse, id, name, password, role);
};

#endif