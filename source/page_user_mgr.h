#ifndef PAGE_USER_MGR_H
#define PAGE_USER_MGR_H

#include <QWidget>

#include <qtmetamacros.h>
#include "model_usr_mgr.h"
namespace Ui
{
class PageUserMgr;
}

class PageUserMgr : public QWidget
{
    Q_OBJECT

  public:
    explicit PageUserMgr(QWidget* parent = nullptr);
    ~PageUserMgr();

    void updateUserInfoList();

  private:
    Ui::PageUserMgr* ui;
    ModelUserMgr* _modelUserMgr;

  signals:
    void goBack();
};

#endif  // PAGE_USER_MGR_H
