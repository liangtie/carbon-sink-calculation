#include <QMessageBox>

#include "mainwindow.h"

#include <qwidget.h>

#include "./ui_mainwindow.h"
#include "network_interaction.h"
#include "page_history.h"
#include "page_input_param.h"
#include "page_login.h"
#include "page_user_mgr.h"
#include "user_role.h"
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
            [this](bool show_mgr)
            {
                _pageUserMgr->updateUserInfoList();
                if (show_mgr)
                    ui->stackedWidget->setCurrentWidget(_pageUserMgr);
            });

    connect(&NetworkInteraction::getInstance(),
            &NetworkInteraction::resultReady,
            this,
            [this]()
            {
                _pageHistory->updateHistory(
                    NetworkInteraction::getInstance().getResultFetched());
                ui->stackedWidget->setCurrentWidget(_pageHistory);
            });

    connect(_pageHistory,
            &PageHistory::goBack,
            this,
            [this] { ui->stackedWidget->setCurrentWidget(_pageInputParam); });
    connect(_pageUserMgr,
            &PageUserMgr::goBack,
            this,
            [this] { ui->stackedWidget->setCurrentWidget(_pageInputParam); });

    connect(_pageInputParam,
            &PageInputParam::show_history,
            this,
            []() { NetworkInteraction::getInstance().startFetchResult(); });

    connect(_pageInputParam,
            &PageInputParam::show_usr_mgr,
            this,
            []() { NetworkInteraction::getInstance().getUserList(true); });
}

MainWindow::~MainWindow()
{
    delete ui;
}
