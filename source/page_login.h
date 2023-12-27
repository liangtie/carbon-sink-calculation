#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>

#include <qtmetamacros.h>

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
    void AccountVerifyPass();

  private:
    Ui::PageLogin* ui;
};

#endif  // PAGE_LOGIN_H
