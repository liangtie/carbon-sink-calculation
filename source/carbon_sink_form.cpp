#include <cmath>
#include <string>

#include "carbon_sink_form.h"

#include "constant.h"
#include "http_param.h"
#include "network_interaction.h"

int CarbonSinkForm::year() const
{
    return _year;
}

void CarbonSinkForm::setYear(int newYear)
{
    _year = newYear;
}

double CarbonSinkForm::area() const
{
    return _area;
}

void CarbonSinkForm::setArea(double newArea)
{
    _area = newArea;
}

double CarbonSinkForm::circumference() const
{
    return _circumference;
}

void CarbonSinkForm::setCircumference(double newCircumference)
{
    _circumference = newCircumference;
}

int CarbonSinkForm::floorCount() const
{
    return _floorCount;
}

void CarbonSinkForm::setFloorCount(int newFloorCount)
{
    _floorCount = newFloorCount;
}

double CarbonSinkForm::height() const
{
    return _height;
}

void CarbonSinkForm::setHeight(double newHeight)
{
    _height = newHeight;
}

int CarbonSinkForm::buildingCount() const
{
    return _buildingCount;
}

void CarbonSinkForm::setBuildingCount(int newBuildingCount)
{
    _buildingCount = newBuildingCount;
}

int CarbonSinkForm::buildingType() const
{
    return _buildingType;
}

void CarbonSinkForm::setBuildingType(int newBuildingType)
{
    _buildingType = newBuildingType;
}

QString CarbonSinkForm::concreteStrengthGrade() const
{
    return _concreteStrengthGrade;
}

void CarbonSinkForm::setConcreteStrengthGrade(
    const QString& newConcreteStrengthGrade)
{
    _concreteStrengthGrade = newConcreteStrengthGrade;
}

QString CarbonSinkForm::buildingStructureType() const
{
    return _buildingStructureType;
}

void CarbonSinkForm::setBuildingStructureType(
    const QString& newBuildingStructureType)
{
    _buildingStructureType = newBuildingStructureType;
}

QString CarbonSinkForm::cementType() const
{
    return _cementType;
}

void CarbonSinkForm::setCementType(const QString& newCementType)
{
    _cementType = newCementType;
}

QString CarbonSinkForm::cementStrengthGrade() const
{
    return _cementStrengthGrade;
}

void CarbonSinkForm::setCementStrengthGrade(
    const QString& newCementStrengthGrade)
{
    _cementStrengthGrade = newCementStrengthGrade;
}

QString CarbonSinkForm::address() const
{
    return _province + _city + _county;
}

double CarbonSinkForm::carbonSink()
{
    using namespace constant;

    if (_result.has_value())
        return *_result;

    const auto t = year();
    const auto A = area();
    const auto P = circumference();
    const auto F = floorCount();
    const auto H = height();
    const auto AF = A*F;
    const auto AF2 = AF*2;
    const auto FH = F* H;
    const auto FHP = FH * P;
    const auto FHP2 = FHP * 2;
    const auto add = AF2 + FHP2 +  A;
    const auto Ae = add;
    const auto [m, n] = BuildingTypeFactors.at(buildingType());
    const auto Aen =  std::pow(Ae , n);
    const auto t0_5 = std::pow(t, 0.5);
      const auto a =
            CementType.value(cementType()).value(cementStrengthGrade());
    const auto Nabc =  buildingCount() * a * ConcreteStrengthGrade.at(concreteStrengthGrade()) *  BuildingStructureType.at(buildingStructureType());

    const auto y = m * Aen * t0_5 * Nabc;
       _result = std::round(y );
        return *_result;
}

ResultForm CarbonSinkForm::toFrom()
{
    using namespace constant;

    ResultForm form;
    form.province = _province.toStdString();
    form.city = _city.toStdString();
    form.county = _county.toStdString();
    form.architecturalType =
        ReadableBuildingType.at(_buildingType).toStdString();
    form.cementType = _cementType.toStdString();
    form.cementLevel = _cementStrengthGrade.toStdString();
    form.concreteLevel = _concreteStrengthGrade.toStdString();
    form.structureType = _buildingStructureType.toStdString();
    form.structureTime = (_year);
    form.structureArea = (_area);
    form.structureLine = (_circumference);
    form.structureNum = (_floorCount);
    form.structureHigh = (_height);
    form.structureCount = _buildingCount;
    form.calculateResult = std::to_string(carbonSink());
    form.createTime = _createTime.toStdString();
    form.userId = NetworkInteraction::getInstance().getLoginResult().id;
    return form;
}

inline auto toString(std::string const& s)
{
    return QString::fromStdString(s);
}

void CarbonSinkForm::fromForm(ResultForm const& form)
{
    using namespace constant;

    _province = toString(form.province);
    _city = toString(form.city);
    _county = toString(form.county);
    _buildingType = ([&](){

        for(const auto& [c,v ] : ReadableBuildingType){
            if(v.toStdString() ==  form.architecturalType )
                return c;
        }
                    return 0;
    }());
    _cementType = toString(form.cementType);
    _cementStrengthGrade = toString(form.cementLevel);
    _concreteStrengthGrade = toString(form.concreteLevel);
    _buildingStructureType = toString(form.structureType);
    _year = (form.structureTime);
    _area = (form.structureArea);
    _circumference = (form.structureLine);
    _floorCount = (form.structureNum);
    _height = (form.structureHigh);
    _buildingCount = (form.structureCount);
    // _result = std::stod(form.calculateResult);
    _createTime = toString(form.createTime);
}

QString CarbonSinkForm::province() const
{
    return _province;
}

void CarbonSinkForm::setProvince(const QString& newProvince)
{
    _province = newProvince;
}

QString CarbonSinkForm::city() const
{
    return _city;
}

void CarbonSinkForm::setCity(const QString& newCity)
{
    _city = newCity;
}

QString CarbonSinkForm::county() const
{
    return _county;
}

void CarbonSinkForm::setCounty(const QString& newCounty)
{
    _county = newCounty;
}

QString CarbonSinkForm::createTime() const
{
    return _createTime;
}
