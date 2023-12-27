#ifndef PAGE_INPUT_PARAM_H
#define PAGE_INPUT_PARAM_H

#include <QWidget>

namespace Ui {
class PageInputParam;
}

class PageInputParam : public QWidget
{
    Q_OBJECT

  public:
    explicit PageInputParam(QWidget *parent = nullptr);
    ~PageInputParam();

  private:
    Ui::PageInputParam *ui;
};

#endif // PAGE_INPUT_PARAM_H
