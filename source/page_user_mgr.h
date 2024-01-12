#ifndef PAGE_USER_MGR_H
#define PAGE_USER_MGR_H

#include <QWidget>

namespace Ui {
class PageUserMgr;
}

class PageUserMgr : public QWidget
{
    Q_OBJECT

  public:
    explicit PageUserMgr(QWidget *parent = nullptr);
    ~PageUserMgr();

  private:
    Ui::PageUserMgr *ui;
};

#endif // PAGE_USER_MGR_H
