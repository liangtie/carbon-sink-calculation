#include "page_single_record.h"

#include "constant.h"
#include "ui_page_single_record.h"

PageSingleRecord::PageSingleRecord(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::PageSingleRecord)
{
    ui->setupUi(this);
}

PageSingleRecord::~PageSingleRecord()
{
    delete ui;
}

template<class T>
auto toString(T const& v)
{
    return QString("%1").arg(v);
}

void PageSingleRecord::init(CarbonSinkForm const& form)
{
    using namespace constant;
    ui->lb_location->setText(toString(form.address()));
    ui->lb_year->setText(toString(form.year()));
    ui->lb_building_area->setText(toString(form.area()));
    ui->lb_circumference->setText(toString(form.circumference()));
    ui->lb_floor_count->setText(toString(form.floorCount()));
    ui->lb_height->setText(toString(form.height()));
    ui->lb_building_count->setText(toString(form.buildingCount()));
    ui->lb_building_t->setText(
        toString(ReadableBuildingType.at(form.buildingType())));
    ui->lb_concrete_grade->setText(form.concreteStrengthGrade());
    ui->lb_structure_t->setText(toString(form.buildingStructureType()));
    ui->lb_cement_t->setText(toString(form.cementType()));
    ui->lb_cement_grade->setText(toString(form.concreteStrengthGrade()));
    ui->lb_result->setText(toString(  static_cast<unsigned long long>( form.carbonSink())));
    ui->lb_record_time->setText(form.createTime());
}
