
#include "carbon_sink_exporter.h"
#include "carbon_sink_form.h"
#include "constant.h"
#include "utils.h"


#include <qdatetime.h>
#include <xlnt/xlnt.hpp>
#include <QDateTime>
#include <QString>
#include <utility>


constexpr auto EXCEL_SUFFIX = ".xlsx";

static const auto FORM_HEADER = std::unordered_map<int, std::string> {
    std::make_pair(CarbonSinkForm::ADDRESS, "建筑地址"),
    std::make_pair(CarbonSinkForm::YEAR, "时间"),
    std::make_pair(CarbonSinkForm::AREA, "面积"),
    std::make_pair(CarbonSinkForm::CIRCUM, "周长"),
    std::make_pair(CarbonSinkForm::HEIGHT, "建筑层高"),
    std::make_pair(CarbonSinkForm::BUILDING_COUNT, "建筑数量"),
    std::make_pair(CarbonSinkForm::BUILDING_TYPE, "建筑结构类型"),
    std::make_pair(CarbonSinkForm::CONCRETE_STRENGTH_GRADE, "混凝土强度等级"),
    std::make_pair(CarbonSinkForm::BUILDING_STRUCTURE_TYPE, "建筑结构类型"),
    std::make_pair(CarbonSinkForm::CEMENT_TYPE, "水泥类型"),
    std::make_pair(CarbonSinkForm::CEMENT_STRENGTH_GRADE, "水泥强度等级"),
    std::make_pair(CarbonSinkForm::CARBON_SINK, "碳汇量(KG)"),
    std::make_pair(CarbonSinkForm::FLOOR_COUNT, "楼层数"),
    std::make_pair(CarbonSinkForm::CURRENT_DATE_TIME, "计算时间")};

void CarbonSinkExporter::exportToExcel(
    std::list<CarbonSinkFormPtr> const& forms, QString& fp)
{
    xlnt::workbook wb;
    xlnt::worksheet ws = wb.active_sheet();
    using namespace constant;
    for (const auto& [c, v] : FORM_HEADER) {
        auto headerStyle = wb.create_style("bold");
        auto col = c + 1;
        ws.cell(col, 1).value(v);
        ws.cell(col, 1).style(headerStyle);
    }

    auto row = 1;
    for (const auto& f : forms) {
        ++row;

        for (int c = CarbonSinkForm::BEGIN; c < CarbonSinkForm::END; c++) {
            auto col = c + 1;
            switch (static_cast<CarbonSinkForm::Columns>(c)) {
                case CarbonSinkForm::ADDRESS:
                    ws.cell(col, row).value(f->address().toStdString());
                    break;
                case CarbonSinkForm::YEAR:
                    ws.cell(col, row).value(f->year());
                    break;
                case CarbonSinkForm::AREA:
                    ws.cell(col, row).value(f->area());
                    break;
                case CarbonSinkForm::CIRCUM:
                    ws.cell(col, row).value(f->circumference());
                    break;

                case CarbonSinkForm::HEIGHT:
                    ws.cell(col, row).value(f->height());
                    break;

                case CarbonSinkForm::FLOOR_COUNT:
                    ws.cell(col, row).value(f->floorCount());
                    break;

                case CarbonSinkForm::BUILDING_COUNT:
                    ws.cell(col, row).value(f->buildingCount());

                    break;

                case CarbonSinkForm::BUILDING_TYPE:
                    ws.cell(col, row).value(
                        ReadableBuildingType.at(f->buildingType())
                            .toStdString());
                    break;

                case CarbonSinkForm::CONCRETE_STRENGTH_GRADE:
                    ws.cell(col, row).value(
                        f->concreteStrengthGrade().toStdString());

                    break;

                case CarbonSinkForm::BUILDING_STRUCTURE_TYPE:
                    ws.cell(col, row).value(
                        f->buildingStructureType().toStdString());

                    break;

                case CarbonSinkForm::CEMENT_TYPE:
                    ws.cell(col, row).value(f->cementType().toStdString());

                    break;

                case CarbonSinkForm::CEMENT_STRENGTH_GRADE:
                    ws.cell(col, row).value(
                        f->cementStrengthGrade().toStdString());

                    break;

                case CarbonSinkForm::CARBON_SINK:
                    ws.cell(col, row).value(f->carbonSink());
                    break;
                case CarbonSinkForm::CURRENT_DATE_TIME:
                    ws.cell(col, row).value(Utils::getCurrentDateTime());
                    break;
            }
        }
    }

    if (!fp.endsWith(EXCEL_SUFFIX))
        fp += EXCEL_SUFFIX;
    wb.save(fp.toStdString());
}