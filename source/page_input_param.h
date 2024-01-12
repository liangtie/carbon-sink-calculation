#ifndef PAGE_INPUT_PARAM_H
#define PAGE_INPUT_PARAM_H

#include <QWidget>
#include <memory>
#include <list>
namespace Ui {
class PageInputParam;
}

class CarbonSinkForm;
using CarbonSinkFormPtr = std::shared_ptr<CarbonSinkForm>;
class PcaModel;
class PageInputParam : public QWidget
{
    Q_OBJECT

  public:
    explicit PageInputParam(QWidget *parent = nullptr);
    ~PageInputParam();

    void clearForm();

    [[nodiscard]] auto formIsValid() const -> bool;

    [[nodiscard]] auto exportForm() const ->  CarbonSinkFormPtr;

    [[nodiscard]] int role() const;
    void setRole(int newRole);

  private:
    Ui::PageInputParam *ui;
    std::unique_ptr<PcaModel> _pcaModel;
    std::list<CarbonSinkFormPtr> _forms;
    int _role{};
};

#endif // PAGE_INPUT_PARAM_H
