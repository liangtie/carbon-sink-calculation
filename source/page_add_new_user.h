#ifndef PAGE_ADD_NEW_USER_H
#define PAGE_ADD_NEW_USER_H

#include <QWidget>

namespace Ui {
class PageAddNewUser;
}

class PageAddNewUser : public QWidget
{
    Q_OBJECT

  public:
    explicit PageAddNewUser(QWidget *parent = nullptr);
    ~PageAddNewUser();

  private:
    Ui::PageAddNewUser *ui;
};

#endif // PAGE_ADD_NEW_USER_H
