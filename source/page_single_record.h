#ifndef PAGE_SINGLE_RECORD_H
#define PAGE_SINGLE_RECORD_H

#include <QWidget>
#include "carbon_sink_form.h"

namespace Ui {
class PageSingleRecord;
}

class PageSingleRecord : public QWidget
{
    Q_OBJECT

  public:
    explicit PageSingleRecord(QWidget *parent = nullptr);
    ~PageSingleRecord();
    void init(CarbonSinkForm const& form);

  private:
    Ui::PageSingleRecord *ui;
};

#endif // PAGE_SINGLE_RECORD_H
