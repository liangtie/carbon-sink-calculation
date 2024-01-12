#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
namespace Ui
{
class PageLogin;
}

class PageLogin : public QWidget
{
    Q_OBJECT

  public:
    explicit PageLogin(QWidget* parent = nullptr);
    ~PageLogin();

  signals:
    void accountVerifyPass(int role);

  private:
    Ui::PageLogin* ui;
};

#endif  // PAGE_LOGIN_H
