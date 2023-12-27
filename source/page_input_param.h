#ifndef PAGE_INPUT_PARAM_H
#define PAGE_INPUT_PARAM_H

#include <QWidget>
#include <memory>
#include "pca_model.h"
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
    std::unique_ptr<PcaModel> _pcaModel;
};

#endif // PAGE_INPUT_PARAM_H
