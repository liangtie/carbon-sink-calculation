#include "page_user_mgr.h"
#include "ui_page_user_mgr.h"

PageUserMgr::PageUserMgr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageUserMgr)
{
    ui->setupUi(this);
}

PageUserMgr::~PageUserMgr()
{
    delete ui;
}
