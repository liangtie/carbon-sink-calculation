#include "page_input_param.h"
#include "ui_page_input_param.h"

PageInputParam::PageInputParam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageInputParam)
{
    ui->setupUi(this);
}

PageInputParam::~PageInputParam()
{
    delete ui;
}
