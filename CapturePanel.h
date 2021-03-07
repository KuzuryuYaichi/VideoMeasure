#ifndef CAPTURE_PANEL_H
#define CAPTURE_PANEL_H

#include <QtWidgets/QWidget>
#include <QLayout>
#include <QtCharts/QChartGlobal>
#include "CQtOpencvViewerGl.h"
#include <QtWidgets/QTableWidget>
#include "CustomScatterTableModel.h"
#include "MyVideo.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

class CapturePanel : public QWidget
{
    Q_OBJECT
public:
    explicit CapturePanel(QWidget* parent = 0);
    explicit CapturePanel(QString title, QWidget* parent = 0);
    ~CapturePanel();
    void SetMapper(int xRow, int yRow);
    void ModelSetData(std::vector<cv::Point>& result);


    //private Q_SLOTS:
    //    void updateUI();

private:
    QChart* createScatterChart(QString title) const;
    QChart* createScatterChart() const;
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;

public:
    CQtOpenCVViewerGl* MatDisplay = nullptr;

private:
    QVBoxLayout* layout;
    QChartView* chartView;
    QTableView* m_tableWidget;
    CustomScatterTableModel* model;
};

#endif /* THEMEWIDGET_H */
