#include <QMessageBox>
#include <string>

#include "dialog_add_new_user.h"

#include <qdialog.h>

#include "http_param.h"
#include "network_interaction.h"
#include "ui_dialog_add_new_user.h"
#include "user_role.h"

DialogAddNewUser::DialogAddNewUser(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DialogAddNewUser)
{
    ui->setupUi(this);

    ui->comboRole->addItem("普通用户", UserRoles::NORMAL_USER);
    ui->comboRole->addItem("管理员", UserRoles::ADMIN);

    connect(ui->buttonBox,
            &QDialogButtonBox::accepted,
            this,
            [this]()
            {
                AddUserForm form;
                form.account = ui->editAccount->text().toStdString();
                form.company = ui->editCompany->text().toStdString();
                form.name = ui->editUser->text().toStdString();
                form.password = ui->editPassword->text().toStdString();
                form.role =
                    std::to_string(ui->comboRole->currentData().toInt());
                NetworkInteraction::getInstance().addUser(form);
            });

    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::close);
}

DialogAddNewUser::~DialogAddNewUser()
{
    delete ui;
}
