#ifndef PAGE_INPUT_PARAM_H
#define PAGE_INPUT_PARAM_H

#include <QWidget>
#include <memory>
namespace Ui {
class PageInputParam;
}

struct CarbonSinkForm;
using CarbonSinkFormPtr = std::shared_ptr<CarbonSinkForm>;
class PcaModel;
class PageInputParam : public QWidget
{
    Q_OBJECT

  public:
    explicit PageInputParam(QWidget *parent = nullptr);
    ~PageInputParam();

    [[nodiscard]] auto exportForm() const ->  CarbonSinkFormPtr;

  private:
    Ui::PageInputParam *ui;
    std::unique_ptr<PcaModel> _pcaModel;
};

#endif // PAGE_INPUT_PARAM_H
