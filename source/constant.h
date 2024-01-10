#ifndef CONSTANT_H
#define CONSTANT_H

#include <QMap>
#include <QString>
#include <map>
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

struct BuildTypeFactor
{
    double m;
    double n;
};
static const auto BuildingTypeFactors = std::map<int, BuildTypeFactor> {

    std::make_pair(RB, BuildTypeFactor {0.368, 0.992}),
    std::make_pair(IB, BuildTypeFactor {0.511, 0.976}),
    std::make_pair(CB, BuildTypeFactor {0.523, 0.968}),
    std::make_pair(PB, BuildTypeFactor {0.421, 0.985}),
    std::make_pair(OB, BuildTypeFactor {0.479, 0.980}),

};

static const auto ReadableBuildingType =
    std::map<int, QString> {std::make_pair(RB, "住宅建筑"),
                            std::make_pair(IB, "工业建筑"),
                            std::make_pair(CB, "商业建筑"),
                            std::make_pair(PB, "公共建筑"),
                            std::make_pair(OB, "其他建筑")

    };

static const auto ConcreteStrengthGrade = std::map<QString, double> {
    std::make_pair("C10", 0.61),
    std::make_pair("C15", 0.72),
    std::make_pair("C20", 0.803),
    std::make_pair("C25", 0.995),
    std::make_pair("C30", 1),
    std::make_pair("C35", 1.005),
    std::make_pair("C40", 1.048),
    std::make_pair("C45", 1.155),
    std::make_pair("C50", 1.228),

};

static const auto BuildingStructureType = std::map<QString, double> {
    std::make_pair("砖混结构", 0.86),
    std::make_pair("钢筋混凝土结构", 1),
};

static const auto CementType = QMap<QString, QMap<QString, double>> {
    std::make_pair("普通硅酸盐水泥",
                   QMap<QString, double> {
                       std::make_pair("42.5", 1),
                       std::make_pair("42.5R", 1),
                       std::make_pair("52.5", 0.989),
                       std::make_pair("52.5R", 0.968),
                       std::make_pair("62.5", 0.947),
                       std::make_pair("62.5R", 0.942),

                   }),
    std::make_pair("矿渣硅酸盐水泥",
                   QMap<QString, double> {
                       std::make_pair("32.5", 0.526),
                       std::make_pair("32.5R", 0.474),
                       std::make_pair("42.5", 0.421),
                       std::make_pair("42.5R", 0.368),
                       std::make_pair("52.5", 0.368),
                       std::make_pair("52.5R", 0.316),

                   }),
    std::make_pair("粉煤硅酸盐灰水泥",
                   QMap<QString, double> {
                       std::make_pair("32.5", 0.842),
                       std::make_pair("32.5R", 0.821),
                       std::make_pair("42.5", 0.789),
                       std::make_pair("42.5R", 0.737),
                       std::make_pair("52.5", 0.684),
                       std::make_pair("52.5R", 0.632),
                   }),
    std::make_pair("火山硅酸盐灰水泥",
                   QMap<QString, double> {
                       std::make_pair("32.5R", 0.842),
                       std::make_pair("42.5", 0.789),
                       std::make_pair("42.5R", 0.737),
                       std::make_pair("52.5", 0.632),
                       std::make_pair("52.5R", 0.526),
                   }),
    std::make_pair("复合硅酸盐水泥",
                   QMap<QString, double> {
                       std::make_pair("32.5", 0.842),
                       std::make_pair("32.5R", 0.737),
                       std::make_pair("42.5", 0.684),
                       std::make_pair("42.5R", 0.632),
                       std::make_pair("52.5", 0.579),
                       std::make_pair("52.5R", 0.526),
                   }),

};

}  // namespace constant

#endif