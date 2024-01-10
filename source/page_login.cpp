#include "page_login.h"

#include <qabstractbutton.h>
#include <qmessagebox.h>

#include "network_interaction.h"
#include "ui_page_login.h"
#include "user_role.h"
#include "dialog_add_new_user.h"

PageLogin::PageLogin(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::PageLogin)
{
    ui->setupUi(this);

    connect(ui->btnLogin,
            &QAbstractButton::clicked,
            this,
            [this]()
            {
                NetworkInteraction::getInstance().login(
                    {ui->editUser->text().toStdString(),
                     ui->editPass->text().toStdString()});

                AccountVerifyPass(UserRoles::ADMIN);
            });
    connect(ui->btnAddUser,
            &QPushButton::clicked,
            this,
            [&]()
            {
                DialogAddNewUser d(this);
                d.exec();
            });

}

PageLogin::~PageLogin()
{
    delete ui;
}
