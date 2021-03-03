#ifndef VIDEO_PANEL_H
#define VIDEO_PANEL_H

#include <QtWidgets/QWidget>
#include <QLayout>
#include "CQtOpencvViewerGl.h"
#include "ui_VideoWidget.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
QT_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

class VideoPanel : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPanel(QWidget* parent = 0);
    explicit VideoPanel(QString title, QWidget* parent = 0);
    ~VideoPanel();

//private Q_SLOTS:
//    void updateUI();

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QVBoxLayout* layout;
    CQtOpenCVViewerGl* MatDisplay = nullptr;
    DataTable m_dataTable;

public:
    Ui_VideoWidget* m_ui;
};

#endif /* THEMEWIDGET_H */
