#ifndef PAGE_HISTORY_H
#define PAGE_HISTORY_H

#include <QWidget>

namespace Ui {
class PageHistory;
}

class PageHistory : public QWidget
{
    Q_OBJECT

  public:
    explicit PageHistory(QWidget *parent = nullptr);
    ~PageHistory();

  private:
    Ui::PageHistory *ui;
};

#endif // PAGE_HISTORY_H
