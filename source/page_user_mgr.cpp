#include <QTableView>
#include <functional>
#include <map>
#include <utility>

#include "page_user_mgr.h"

#include <qabstractitemmodel.h>
#include <qdialog.h>
#include <qheaderview.h>
#include <qpushbutton.h>
#include <QInputDialog>
#include "dialog_add_new_user.h"
#include "network_interaction.h"
#include "ui_page_user_mgr.h"

PageUserMgr::PageUserMgr(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::PageUserMgr)
    , _modelUserMgr(new ModelUserMgr(this))
{
    ui->setupUi(this);
    ui->tb_users->setModel(_modelUserMgr);
    ui->tb_users->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    ui->tb_users->verticalHeader()->setVisible(false);
    ui->tb_users->setSelectionBehavior(
        QAbstractItemView::SelectionBehavior::SelectRows);


    connect(ui->btn_add, &QPushButton::clicked, this, &PageUserMgr::goBack);
    connect(ui->btn_add,
            &QPushButton::clicked,
            this,
            [this]()
            {
                const auto idx = ui->tb_users->currentIndex();
                if (!idx.isValid())
                    return;
                DialogAddNewUser dialog(this);
                dialog.exec();
            });
    connect(ui->btn_del,
            &QPushButton::clicked,
            this,
            [this]()
            {
                const auto idx = ui->tb_users->currentIndex();
                if (!idx.isValid())
                    return;
                _modelUserMgr->rmUser(idx.row());
            });
    connect(ui->btn_modify,
            &QPushButton::clicked,
            this,
            [this]()
            {
                const auto idx = ui->tb_users->currentIndex();
                if (!idx.isValid())
                    return;
                const auto pass = QInputDialog::getText(this, "修改用户密码", "新密码:");
                if(!pass.isEmpty())
                {
                    auto info = _modelUserMgr->getUsrInfo(idx.row());
                    info.password = pass.toStdString();
                    NetworkInteraction::getInstance().updateUserPassword(std::move(info));
                }

            });
}

PageUserMgr::~PageUserMgr()
{
    delete ui;
}

void PageUserMgr::updateUserInfoList()
{
    _modelUserMgr->setUsers(NetworkInteraction::getInstance().getUserInfo());
}
