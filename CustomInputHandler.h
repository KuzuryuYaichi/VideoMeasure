#ifndef CUSTOMINPUTHANDLER_H
#define CUSTOMINPUTHANDLER_H

#include <QtDataVisualization/QAbstract3DInputHandler>

using namespace QtDataVisualization;

class CustomInputHandler : public QAbstract3DInputHandler
{
    Q_OBJECT
public:
    explicit CustomInputHandler(QObject* parent = 0);

    virtual void mouseMoveEvent(QMouseEvent* event, const QPoint& mousePos);
    virtual void wheelEvent(QWheelEvent* event);
};

#endif
