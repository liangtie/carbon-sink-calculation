#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class PageLogin;
class PageInputParam;
class PageHistory;
class PageUserMgr;
class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow* ui;
    PageLogin* _pageLogin;
    PageInputParam* _pageInputParam;
    PageHistory* _pageHistory;
    PageUserMgr* _pageUserMgr;

};
#endif  // MAINWINDOW_H
