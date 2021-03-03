#include "VideoWidget.h"
#include "ui_themewidget.h"

VideoWidget::VideoWidget(QWidget* parent) :
    QWidget(parent),
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7)
{
    layout = new QHBoxLayout(this);
    videoPanel[0] = new VideoPanel("Camera X", this);
    videoPanel[1] = new VideoPanel("Camera Y", this);
    videoPanel[2] = new VideoPanel("Camera Z", this);
    for (auto& v : videoPanel)
        layout->addWidget(v);
}

VideoWidget::~VideoWidget()
{

}

void VideoWidget::updateUI()
{
 
}

