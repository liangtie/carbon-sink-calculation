#include "page_add_new_user.h"
#include "ui_page_add_new_user.h"

PageAddNewUser::PageAddNewUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageAddNewUser)
{
    ui->setupUi(this);
}

PageAddNewUser::~PageAddNewUser()
{
    delete ui;
}
