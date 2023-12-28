#include <memory>
#include <qcombobox.h>

#include "page_input_param.h"
#include "pca_model.h"
#include "ui_page_input_param.h"

PageInputParam::PageInputParam(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::PageInputParam)
    , _pcaModel(std::make_unique<PcaModel>(":/qdarkstyle/light/pca.json"))
{
    ui->setupUi(this);

    connect(ui->cbProvince,
            &QComboBox::currentTextChanged,
            [&](QString const& p)
            {
                ui->cbCity->clear();
                if (p == UN_SELECTED || p.isEmpty())
                    return;
                ui->cbCity->addItems(_pcaModel->getCities(p));
            });

    connect(ui->cbCity,
            &QComboBox::currentTextChanged,
            [&](QString const& p)
            {
                ui->cbCounty->clear();
                if (p == UN_SELECTED || p.isEmpty())
                    return;

                ui->cbCounty->addItems(_pcaModel->getAreas(ui->cbProvince->currentText(),  p));
            });

    ui->cbProvince->addItems(_pcaModel->getProvinces());
}

PageInputParam::~PageInputParam()
{
    delete ui;
}

auto PageInputParam::exportForm() const ->  CarbonSinkFormPtr
{
    return {};
}
