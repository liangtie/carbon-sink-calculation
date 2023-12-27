#ifndef PCA_MODEL_H
#define PCA_MODEL_H

#include <QMap>
#include <QString>
using PCM =
    std::map<std::string, std::map<std::string, std::list<std::string>>>;
static const auto UN_SELECTED = "--";
class PcaModel
{
  public:
    PcaModel(QString const& filePath);
    ~PcaModel();

    auto getProvinces() const -> QStringList;

    auto getCities(QString province) const -> QStringList;

    auto getAreas(QString province, QString city) -> QStringList;

  private:
    PCM _pcm;
};

#endif