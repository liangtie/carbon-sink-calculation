#include <cmath>

#include "carbon_sink_form.h"

#include "constant.h"

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
    return _address;
}

void CarbonSinkForm::setAddress(const QString& newAddress)
{
    _address = newAddress;
}

double CarbonSinkForm::carbonSink() const
{
    using namespace constant;
    const auto t = year();
    const auto A = area();
    const auto P = circumference();
    const auto F = floorCount();
    const auto H = height();
    const auto N = buildingCount();
    constexpr auto t_e = 0.5;

    const auto b = ConcreteStrengthGrade.at(concreteStrengthGrade());
    const auto C = BuildingStructureType.at(buildingStructureType());
    const auto a = CementType.value(cementType()).value(cementStrengthGrade());
    const auto [m, n] = BuildingTypeFactors.at(buildingType());

    auto A_e = A * (F * 2 + 1) + F * H * P * 2;

    return (m * std::pow(A_e, n)) * std::pow(t, t_e) * N * a * b * C;
}
