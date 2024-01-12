#ifndef CARBON_SINK_FORM_H
#define CARBON_SINK_FORM_H

#include <QString>
#include <optional>

#include "utils.h"

struct ResultForm;

class CarbonSinkForm
{
  public:
    enum Columns
    {
        ADDRESS,

        BEGIN = ADDRESS,

        BUILDING_TYPE,

        CEMENT_TYPE,

        CEMENT_STRENGTH_GRADE,

        CONCRETE_STRENGTH_GRADE,

        BUILDING_STRUCTURE_TYPE,

        YEAR,

        AREA,

        CIRCUM,

        FLOOR_COUNT,

        HEIGHT,

        BUILDING_COUNT,

        CARBON_SINK,

        CURRENT_DATE_TIME,

        END = CURRENT_DATE_TIME + 1
    };

    int year() const;
    void setYear(int newYear);

    double area() const;
    void setArea(double newArea);

    double circumference() const;
    void setCircumference(double newCircumference);

    int floorCount() const;
    void setFloorCount(int newFloorCount);

    double height() const;
    void setHeight(double newHeight);

    int buildingCount() const;
    void setBuildingCount(int newBuildingCount);

    int buildingType() const;
    void setBuildingType(int newBuildingType);

    QString concreteStrengthGrade() const;
    void setConcreteStrengthGrade(const QString& newConcreteStrengthGrade);

    QString buildingStructureType() const;
    void setBuildingStructureType(const QString& newBuildingStructureType);

    QString cementType() const;
    void setCementType(const QString& newCementType);

    QString cementStrengthGrade() const;
    void setCementStrengthGrade(const QString& newCementStrengthGrade);

    QString address() const;

    double carbonSink();

    double carbonSink() const { return _result.has_value() ? *_result : 0; }

    ResultForm toFrom();

    void fromForm(ResultForm const& form);

    QString province() const;
    void setProvince(const QString& newProvince);

    QString city() const;
    void setCity(const QString& newCity);

    QString county() const;
    void setCounty(const QString& newCounty);

    QString createTime() const;

  private:
    int _year {};
    double _area {};
    double _circumference {};
    int _floorCount {};
    double _height {};
    int _buildingCount {};
    int _buildingType {};
    QString _concreteStrengthGrade {};
    QString _buildingStructureType {};
    QString _cementType {};
    QString _cementStrengthGrade {};
    std::optional<double> _result;

    QString _province;
    QString _city;
    QString _county;
    QString _createTime = QString::fromStdString(Utils::getCurrentDateTime());
};

#endif
