#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QValidator>
#include <memory>

#include "page_input_param.h"

#include <qcombobox.h>
#include <qfiledialog.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qprocess.h>
#include <qvalidator.h>
#include <qvariant.h>
#include "user_role.h"
#include "carbon_sink_exporter.h"
#include "carbon_sink_form.h"
#include "constant.h"
#include "network_interaction.h"
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

                ui->cbCounty->addItems(
                    _pcaModel->getAreas(ui->cbProvince->currentText(), p));
            });

    connect(ui->cbCementType,
            &QComboBox::currentTextChanged,
            [&](QString const& p)
            {
                ui->cbCementRank->clear();
                if (p.isEmpty())
                    return;

                ui->cbCementRank->addItems(constant::CementType[p].keys());
            });

    ui->cbProvince->addItems(_pcaModel->getProvinces());

    for (const auto& [c, v] : constant::ReadableBuildingType)
        ui->cbBuildingType->addItem(v, c);

    for (const auto& [c, v] : constant::ConcreteStrengthGrade)
        ui->cbConcreteRank->addItem(c, QVariant::fromValue(v));

    for (const auto& [c, v] : constant::BuildingStructureType)
        ui->cbBuildingStructType->addItem(c, QVariant::fromValue(v));

    ui->cbCementType->addItems(constant::CementType.keys());

    ui->editArea->setValidator(new QDoubleValidator);
    ui->editBuildingYear->setValidator(new QIntValidator(0, 200));
    ui->editCircumference->setValidator(new QDoubleValidator);
    ui->editCount->setValidator(new QIntValidator);
    ui->editFloorCount->setValidator(new QIntValidator);
    ui->editHeight->setValidator(new QDoubleValidator);

    connect(
        ui->btnAddNewEntry,
        &QPushButton::clicked,
        this,
        [&]()
        {
            if (QMessageBox::Yes
                == QMessageBox::information(this,
                                            "提示",
                                            "是否提交当前表单?",
                                            QMessageBox::StandardButton::Yes,
                                            QMessageBox::StandardButton::No))
            {
                if (!formIsValid()) {
                    QMessageBox::warning(this, "错误", "无效的表单");
                    return;
                }
                _forms.push_back(exportForm());
            }
        });
    connect(ui->btnCancel, &QPushButton::clicked, this, [&]() { clearForm(); });

    connect(ui->btnConfirm,
            &QPushButton::clicked,
            this,
            [&]()
            {
                if (!formIsValid()) {
                    QMessageBox::warning(this, "错误", "无效的表单");
                    return;
                }

                auto form = exportForm();
                ui->labelResult->setText(
                    QString("%1").arg( static_cast<unsigned long long >(form->carbonSink())));
                NetworkInteraction::getInstance().uploadResult(form->toFrom());
            });

    connect(ui->btnHistory,
            &QPushButton::clicked,
            this,
            [&]() { NetworkInteraction::getInstance().startFetchResult(); });

    connect(
        &NetworkInteraction::getInstance(),
        &NetworkInteraction::resultReady,
        this,
        [&]()
        {
            if (formIsValid()) {
                auto form = exportForm();
                _forms.push_back(form);
                NetworkInteraction::getInstance().uploadResult(form->toFrom());
            }

            std::list<CarbonSinkFormPtr> all_forms =
                NetworkInteraction::getInstance().getResultFetched();

            for (const auto& f : _forms) {
                all_forms.push_back(f);
            }

            if (!all_forms.size())
                return;

            auto savePath =
                QFileDialog::getSaveFileName(this, "选择Excel保存路径" );

            if (savePath.isEmpty())
                return;

            CarbonSinkExporter exporter;
            exporter.exportToExcel(all_forms, savePath);
            savePath.replace("/","\\");
           system(("explorer \"" + savePath + "\"\n").toStdString().c_str() );
        });

    connect(ui->btnHelp,
            &QPushButton::clicked,
            this,
            [&]()
            {
                QMessageBox::information(
                    this,
                    "提示",
                    "建筑建成到今天使用的年数。如建筑于1950年建成，到了今天("
                    "2023年)仍在使用，应填入73。输入1~200 内整数");
            });
}

PageInputParam::~PageInputParam()
{
    delete ui;
}

void PageInputParam::clearForm()
{
    for (const auto& cb : findChildren<QComboBox*>())
        cb->setCurrentIndex(0);

    for (const auto& line : findChildren<QLineEdit*>())
        line->clear();
}

auto PageInputParam::formIsValid() const -> bool
{
    if (ui->cbCounty->currentText() == UN_SELECTED)
        return false;

    for (const auto& line : findChildren<QLineEdit*>())
        if (line->text().isEmpty())
            return false;

    return true;
}

auto PageInputParam::exportForm() const -> CarbonSinkFormPtr
{
    auto form = std::make_shared<CarbonSinkForm>();
    form->setYear(ui->editBuildingYear->text().toInt());
    form->setArea(ui->editArea->text().toDouble());
    form->setCircumference(ui->editCircumference->text().toDouble());
    form->setFloorCount(ui->editFloorCount->text().toInt());
    form->setHeight(ui->editHeight->text().toDouble());
    form->setBuildingCount(ui->editCount->text().toInt());
    form->setBuildingType(ui->cbBuildingType->currentData().toInt());
    form->setConcreteStrengthGrade(ui->cbConcreteRank->currentText());
    form->setBuildingStructureType(ui->cbBuildingStructType->currentText());
    form->setCementType(ui->cbCementType->currentText());
    form->setCementStrengthGrade(ui->cbCementRank->currentText());
    form->setProvince(ui->cbProvince->currentText());
    form->setCity(ui->cbCity->currentText());
    form->setCounty(ui->cbCounty->currentText());
    return form;
}

int PageInputParam::role() const
{
    return _role;
}

void PageInputParam::setRole(int newRole)
{
    _role = newRole;
    ui->btnUserMgr->setVisible(newRole == UserRoles::ADMIN);
}

