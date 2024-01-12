#ifndef PAGE_SINGLE_RECORD_H
#define PAGE_SINGLE_RECORD_H

#include <QWidget>

namespace Ui {
class PageSingleRecord;
}

class PageSingleRecord : public QWidget
{
    Q_OBJECT

  public:
    explicit PageSingleRecord(QWidget *parent = nullptr);
    ~PageSingleRecord();

  private:
    Ui::PageSingleRecord *ui;
};

#endif // PAGE_SINGLE_RECORD_H
