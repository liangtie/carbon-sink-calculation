#include "page_history.h"
#include "ui_page_historystory.h"

PageHistory::PageHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageHistory)
{
    ui->setupUi(this);
}

PageHistory::~PageHistory()
{
    delete ui;
}
