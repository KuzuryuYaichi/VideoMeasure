#ifndef _MY_SCATTER_
#define _MY_SCATTER_

#include <QtDataVisualization/Q3DScatter>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QGeometryRenderer>

using namespace QtDataVisualization;

class MyScatter : public Q3DScatter
{
public:
    MyScatter(const QSurfaceFormat* format = nullptr, QWindow* parent = nullptr);
    ~MyScatter();

private:
    void drawLine(const QVector3D& start, const QVector3D& end, const QColor& color, Qt3DCore::QEntity* _rootEntity);
};

#endif