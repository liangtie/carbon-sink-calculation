#ifndef PAGE_INPUT_PARAM_H
#define PAGE_INPUT_PARAM_H

#include <QWidget>
#include <list>
#include <memory>

#include <qtmetamacros.h>
namespace Ui
{
class PageInputParam;
}

class CarbonSinkForm;
using CarbonSinkFormPtr = std::shared_ptr<CarbonSinkForm>;
class PcaModel;
class PageInputParam : public QWidget
{
    Q_OBJECT

  public:
    explicit PageInputParam(QWidget* parent = nullptr);
    ~PageInputParam();

    void clearForm();

    [[nodiscard]] auto formIsValid() const -> bool;

    [[nodiscard]] auto exportForm() const -> CarbonSinkFormPtr;

    [[nodiscard]] int role() const;
    void setRole(int newRole);

  private:
    Ui::PageInputParam* ui;
    std::unique_ptr<PcaModel> _pcaModel;
    int _role {};

  signals:
    void show_usr_mgr();
    void show_history();
};

#endif  // PAGE_INPUT_PARAM_H
