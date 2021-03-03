#ifndef CAPTUREWIDGET_H
#define CAPTUREWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include "CapturePanel.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

class CaptureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CaptureWidget(QWidget* parent = 0);
    ~CaptureWidget();

private Q_SLOTS:
    void updateUI();

private:
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    void populateThemeBox();
    void populateAnimationBox();
    void populateLegendBox();
    QChart* createScatterChart() const;
    QChart* createScatterChart(QString title) const;

public:
    CapturePanel* capturePanel[3];

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QList<QChartView*> m_charts;
    DataTable m_dataTable;

    Ui_ThemeWidgetForm* m_ui;
};

#endif /* THEMEWIDGET_H */
