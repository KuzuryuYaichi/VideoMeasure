#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QtWidgets/QWidget>
#include "VideoPanel.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget* parent = 0);
    ~VideoWidget();

private Q_SLOTS:
    void updateUI();

public:
    VideoPanel* videoPanel[3];

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QHBoxLayout* layout;
};

#endif /* THEMEWIDGET_H */
