#include "page_login.h"
#include <qabstractbutton.h>
#include "ui_page_login.h"

PageLogin::PageLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageLogin)
{
    ui->setupUi(this);

    connect(ui->btnLogin,&QAbstractButton::clicked , this , &PageLogin::AccountVerifyPass);
}

PageLogin::~PageLogin()
{
    delete ui;
}
