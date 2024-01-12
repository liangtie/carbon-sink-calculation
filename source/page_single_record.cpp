#include "page_single_record.h"
#include "ui_page_single_record.h"

PageSingleRecord::PageSingleRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSingleRecord)
{
    ui->setupUi(this);
}

PageSingleRecord::~PageSingleRecord()
{
    delete ui;
}
