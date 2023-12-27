#include <string>

#include "pca_model.h"

#include <nlohmann/json.hpp>
#include <QFile>
#include <QTextStream>
#include <QDebug>


PcaModel::PcaModel(QString const& filePath) {
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        auto str =stream.readAll().toStdString();
        auto j = nlohmann::json::parse(str);
        j.get_to(_pcm);
    }

}

PcaModel::~PcaModel() = default;

auto PcaModel::getProvinces() const -> QStringList
{
    QStringList l{UN_SELECTED};
    for(const auto& [c,v ] : _pcm)
        l.append(c.c_str());
    return l;
}

auto PcaModel::getCities(QString province) const -> QStringList
{
    QStringList l{UN_SELECTED};
    for(const auto& [c,v ] : _pcm.at(province.toStdString()))
        l.append(c.c_str());
    return l;
}

auto PcaModel::getAreas(QString province, QString city) -> QStringList
{
    QStringList l{UN_SELECTED};
    for(const auto& c : _pcm.at(province.toStdString()).at(city.toStdString()) )
        l.append(c.c_str());
    return l;
}