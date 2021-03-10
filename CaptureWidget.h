#ifndef CAPTUREWIDGET_H
#define CAPTUREWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include "CapturePanel.h"
#include "CustomTableModel.h"

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
    void SetTableWidget();

public:
    CapturePanel* capturePanel[3];

private:
    Ui_ThemeWidgetForm* m_ui;
};

#endif /* THEMEWIDGET_H */
