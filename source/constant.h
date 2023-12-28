#ifndef CONSTANT_H
#define CONSTANT_H

#include <QMap>
#include <utility>

namespace constant
{

enum BuildingType
{
    RB,
    IB,
    CB,
    PB,
    OB
};

static const auto ReadableBuildingType =
    QMap<int, QString> {std::make_pair(RB, "住宅建筑"),
                        std::make_pair(IB, "工业建筑"),
                        std::make_pair(CB, "商业建筑"),
                        std::make_pair(PB, "公共建筑"),
                        std::make_pair(OB, "其他建筑")

    };

enum ConcreteStrengthGrade
{
    C10,
    C15,
    C20,
    C25,
    C30,
    C35,
    C40,
    C45,
    C50
};

static const auto ConcreteStrength = QMap<int, double> {
    std::make_pair(C10, 0.61),
    std::make_pair(C15, 0.72),
    std::make_pair(C20, 0.803),
    std::make_pair(C25, 0.995),
    std::make_pair(C30, 1),
    std::make_pair(C35, 1.005),
    std::make_pair(C40, 1.048),
    std::make_pair(C45, 1.155),
    std::make_pair(C45, 1.228),

};

}  // namespace constant

#endif