#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "page_input_param.h"
#include "page_login.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _pageInputParam = new PageInputParam(ui->stackedWidget);
    _pageLogin = new PageLogin(ui->stackedWidget);
    ui->stackedWidget->addWidget(_pageLogin);
    ui->stackedWidget->addWidget(_pageInputParam);
    connect(_pageLogin,
            &PageLogin::AccountVerifyPass,
            [this]() {

                qDebug() <<"1";
                ui->stackedWidget->setCurrentWidget(_pageInputParam); });
}

MainWindow::~MainWindow()
{
    delete ui;
}
