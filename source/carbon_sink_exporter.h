#ifndef CARBON_SINK_EXPORTER_H
#define CARBON_SINK_EXPORTER_H

#include <memory>
#include <list>
#include <string>
#include <QString>
class CarbonSinkForm;
using CarbonSinkFormPtr = std::shared_ptr<CarbonSinkForm>;
class CarbonSinkExporter
{
public:

    void exportToExcel(std::list<CarbonSinkFormPtr> const& forms , QString & fp);

private:

};

#endif