#ifndef PCA_MODEL_H
#define PCA_MODEL_H

#include <QMap>
#include <QString>

class PcaModel
{
  public:
    PcaModel(QString const& filePath);
    ~PcaModel();

    auto getProvinces() const -> QStringList;

    auto getCities(QString province) const -> QStringList;

    auto getAreas(QString province, QString city) -> QStringList;

  private:
    QMap<QString, QMap<QString, QStringList>> _pcb;
};

#endif