#include <QMessageBox>

#include "mainwindow.h"

#include <qwidget.h>

#include "./ui_mainwindow.h"
#include "network_interaction.h"
#include "page_history.h"
#include "page_input_param.h"
#include "page_login.h"
#include "page_user_mgr.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _pageLogin(new PageLogin(this))
    , _pageInputParam(new PageInputParam(this))
    , _pageHistory(new PageHistory(this))
    , _pageUserMgr(new PageUserMgr(this))
{
    ui->setupUi(this);

    for (auto w : std::list<QWidget*> {
             _pageLogin, _pageInputParam, _pageHistory, _pageUserMgr})
        ui->stackedWidget->addWidget(w);

    connect(&NetworkInteraction::getInstance(),
            &NetworkInteraction::loginSuccess,
            [this](int role)
            {
                _pageInputParam->setRole(role);
                ui->stackedWidget->setCurrentWidget(_pageInputParam);
            });

    connect(&NetworkInteraction::getInstance(),
            &NetworkInteraction::getUsrInfSuccess,
            this,
            [this]()
            {
                _pageUserMgr->updateUserInfoList();
                ui->stackedWidget->setCurrentWidget(_pageUserMgr);
            });

    connect(_pageHistory,
            &PageHistory::goBack,
            this,
            [this] { ui->stackedWidget->setCurrentWidget(_pageInputParam); });
    connect(_pageUserMgr,
            &PageUserMgr::goBack,
            this,
            [this] { ui->stackedWidget->setCurrentWidget(_pageInputParam); });

    NetworkInteraction::getInstance().getUserList();
}

MainWindow::~MainWindow()
{
    delete ui;
}
