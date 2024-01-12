#ifndef PAGE_HISTORY_H
#define PAGE_HISTORY_H

#include <QList>
#include <QWidget>
#include <list>

#include <qwidget.h>

#include "carbon_sink_form.h"
namespace Ui
{
class PageHistory;
}

class PageHistory : public QWidget
{
    Q_OBJECT

  public:
    explicit PageHistory(QWidget* parent = nullptr);
    ~PageHistory();

    void updateHistory(std::list<std::shared_ptr<CarbonSinkForm>> const& forms);

  private:
    Ui::PageHistory* ui;
    std::list<QWidget*> _records;
    std::list<std::shared_ptr<CarbonSinkForm>> _forms;

  signals:
    void goBack();
};

#endif  // PAGE_HISTORY_H
