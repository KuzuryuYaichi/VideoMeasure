#include "CapturePanel.h"

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

CapturePanel::CapturePanel(QWidget* parent) :
    QWidget(parent),
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7),
    m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount))
{
    QVBoxLayout* layout = new QVBoxLayout();
    MatDisplay = new CQtOpenCVViewerGl(this);
    this->setLayout(layout);
    layout->addWidget(MatDisplay);
    chartView = new QChartView(createScatterChart());
    layout->addWidget(chartView);
}

CapturePanel::CapturePanel(QString title, QWidget* parent) :
    QWidget(parent),
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7),
    m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount))
{
    MatDisplay = new CQtOpenCVViewerGl();
    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->addWidget(MatDisplay, 4);
    //slider = new QwtSlider(this);
    //slider->setOrientation(Qt::Horizontal);
    //layout->addWidget(slider);
    chartView = new QChartView(createScatterChart(title));
    layout->addWidget(chartView, 6);
}

CapturePanel::~CapturePanel()
{
    if (MatDisplay != nullptr)
        delete MatDisplay;
}

DataTable CapturePanel::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal)valueCount);
            QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal)m_valueMax / (qreal)valueCount), yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

QChart* CapturePanel::createScatterChart(QString title) const
{
    auto chart = createScatterChart();
    chart->setTitle(title);
    return chart;
}

QChart* CapturePanel::createScatterChart() const
{
    QChart* chart = new QChart();
    QString name("Series ");
    int nameIndex = 0;
    for (const DataList& list : m_dataTable) {
        QScatterSeries* series = new QScatterSeries(chart);
        for (const Data& data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
    chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);
    // Add space to label to add space between labels and axis
    QValueAxis* axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    return chart;
}
