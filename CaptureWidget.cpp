#include "CaptureWidget.h"
#include "ui_themewidget.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>

CaptureWidget::CaptureWidget(QWidget* parent) :
    QWidget(parent),
    m_ui(new Ui_ThemeWidgetForm)
{
    m_ui->setupUi(this);

    capturePanel[0] = new CapturePanel("Camera X", this);
    capturePanel[1] = new CapturePanel("Camera Y", this);
    capturePanel[2] = new CapturePanel("Camera Z", this);

    m_ui->gridLayout->addWidget(capturePanel[0], 1, 0);
    m_ui->gridLayout->addWidget(capturePanel[1], 1, 1);
    m_ui->gridLayout->addWidget(capturePanel[2], 1, 2);

    // Set defaults
    m_ui->antialiasCheckBox->setChecked(true);

    // Set the colors from the light theme as default ones
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);
}

CaptureWidget::~CaptureWidget()
{
    delete m_ui;
}

void CaptureWidget::SetTableWidget(QTableView* m_tableWidget)
{
    for (int i = 0; i < 3; ++i)
    {
        switch (i)
        {
        case 0:capturePanel[i]->SetMapper(0, 1); break;
        case 1:capturePanel[i]->SetMapper(0, 1); break;
        case 2:capturePanel[i]->SetMapper(0, 1); break;
        }
    }
}
