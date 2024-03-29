#include <QFileDialog>

#include "page_history.h"

#include <qalgorithms.h>
#include <qpushbutton.h>

#include "carbon_sink_exporter.h"
#include "network_interaction.h"
#include "page_single_record.h"
#include "ui_page_historystory.h"

PageHistory::PageHistory(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::PageHistory)
{
    ui->setupUi(this);

    connect(
        ui->btn_export_history,
        &QPushButton::clicked,
        this,
        [this]()
        {

            if (!_forms.size())
                return;

            auto savePath =
                QFileDialog::getSaveFileName(this, "选择Excel保存路径");

            if (savePath.isEmpty())
                return;

            CarbonSinkExporter exporter;
            exporter.exportToExcel(_forms, savePath);
            savePath.replace("/", "\\");
            system(("explorer \"" + savePath + "\"\n").toStdString().c_str());
        });

        connect(ui->btn_back,&QPushButton::clicked , this, &PageHistory::goBack);
}

PageHistory::~PageHistory()
{
    delete ui;
}

void PageHistory::updateHistory(
    std::list<std::shared_ptr<CarbonSinkForm>> const& forms)
{
    qDeleteAll(_records);
    std::list<QWidget*> records;

    for (const auto& f : forms) {
        auto w = new PageSingleRecord(this);
        w->init(*f);
        ui->lay_main->addWidget(w);
    }

    _records = records;
    _forms = forms;
}
