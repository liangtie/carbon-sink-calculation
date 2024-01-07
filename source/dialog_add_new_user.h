#ifndef DIALOG_ADD_NEW_USER_H
#define DIALOG_ADD_NEW_USER_H

#include <QDialog>

namespace Ui {
class DialogAddNewUser;
}

class DialogAddNewUser : public QDialog
{
    Q_OBJECT

  public:
    explicit DialogAddNewUser(QWidget *parent = nullptr);
    ~DialogAddNewUser();

  private:
    Ui::DialogAddNewUser *ui;
};

#endif // DIALOG_ADD_NEW_USER_H
