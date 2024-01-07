#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "network_interaction.h"
#include "page_input_param.h"
#include "page_login.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _pageInputParam = new PageInputParam(ui->stackedWidget);
    _pageLogin = new PageLogin(ui->stackedWidget);
    ui->stackedWidget->addWidget(_pageLogin);
    ui->stackedWidget->addWidget(_pageInputParam);

    connect(&NetworkInteraction::getInstance(),
           &NetworkInteraction::LoginSuccess,
            [this](int role)
            {
                _pageInputParam->updateUserRole(role);
                ui->stackedWidget->setCurrentWidget(_pageInputParam);
            });

    connect(&NetworkInteraction::getInstance(),
            &NetworkInteraction::AddUserSuccess,
            this,
            [this](bool b)
            {
                if (b) {
                    QMessageBox::information(this, "提示", "新建用户成功");
                } else {
                    QMessageBox::warning(this, "提示", "新建用户失败");
                }
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}
