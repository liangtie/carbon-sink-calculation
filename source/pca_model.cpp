#include "pca_model.h"

static const auto UN_SELECTED = "--";

PcaModel::PcaModel(QString const& filePath) {}

PcaModel::~PcaModel() = default;

auto PcaModel::getProvinces() const -> QStringList
{
    return _pcb.keys();
}

auto PcaModel::getCities(QString province) const -> QStringList
{
    return _pcb[province].keys();
}

auto PcaModel::getAreas(QString province, QString city) -> QStringList
{
    return _pcb[province][city];
}