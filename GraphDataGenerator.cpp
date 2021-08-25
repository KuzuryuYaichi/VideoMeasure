#include "GraphDataGenerator.h"

#define USE_STATIC_DATA

using namespace QtDataVisualization;

GraphDataGenerator::GraphDataGenerator(Q3DScatter* bargraph, QTableView* tableWidget, CustomTableModel* model):
    m_graph(bargraph),
    m_dataTimer(0),
    m_columnCount(100),
    m_rowCount(50),
    m_tableWidget(tableWidget),
    model(model)
{
    //! [5]
    // Set up bar specifications; make the bars as wide as they are deep,
    // and add a small space between them
    //m_graph->setBarThickness(1.0f);
    //m_graph->setBarSpacing(QSizeF(0.2, 0.2));

    //! [5]
#ifndef USE_STATIC_DATA
    // Set up sample space; make it as deep as it's wide
    m_graph->rowAxis()->setRange(0, m_rowCount);
    m_graph->columnAxis()->setRange(0, m_columnCount);
    m_tableWidget->setColumnCount(m_columnCount);

    // Set selection mode to full
    m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemRowAndColumn);

    // Hide axis labels by explicitly setting one empty string as label list
    m_graph->rowAxis()->setLabels(QStringList(QString()));
    m_graph->columnAxis()->setLabels(QStringList(QString()));

    m_graph->seriesList().at(0)->setItemLabelFormat(QStringLiteral("@valueLabel"));
#else
    // Set selection mode to slice row
    m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow | QAbstract3DGraph::SelectionSlice);
#endif

    // Set theme
    m_graph->activeTheme()->setType(Q3DTheme::ThemeArmyBlue);

    // Set font
    m_graph->activeTheme()->setFont(QFont("Impact", 20));

    // Set preset camera position
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFrontLow);

    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
}

GraphDataGenerator::~GraphDataGenerator()
{
    if (m_dataTimer) {
        m_dataTimer->stop();
        delete m_dataTimer;
    }
    delete m_graph;
}

void GraphDataGenerator::start()
{
#ifndef USE_STATIC_DATA
    m_dataTimer = new QTimer();
    m_dataTimer->setTimerType(Qt::CoarseTimer);
    QObject::connect(m_dataTimer, &QTimer::timeout, this, &GraphDataGenerator::addRow);
    m_dataTimer->start(0);
    m_tableWidget->setFixedWidth(m_graph->width());
#else
    //! [8]
    setupModel();
    // Table needs to be shown before the size of its headers can be accurately obtained, so we postpone it a bit
    m_dataTimer = new QTimer();
    m_dataTimer->setSingleShot(true);
    QObject::connect(m_dataTimer, &QTimer::timeout, this, &GraphDataGenerator::fixTableSize);
    m_dataTimer->start(0);
    //! [8]
#endif
}

void GraphDataGenerator::setupModel()
{
    //! [9]
    // Set up row and column names
    QStringList points;
    points << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10";
    QStringList positions;
    positions << "X Axis" << "Y Axis" << "Z Axis";

    // Set up data
    float point_val[10][3];
    //! [9]

    // Add labels
    //! [10]
    m_graph->axisY()->setTitle("Y Axis");
    m_graph->axisY()->setTitleVisible(true);
    m_graph->axisX()->setTitle("X Axis");
    m_graph->axisX()->setTitleVisible(true);
    m_graph->axisZ()->setTitle("Z Axis");
    m_graph->axisZ()->setTitleVisible(true);
    //m_graph->valueAxis()->setLabelFormat("%.1f h");
    //! [10]

    //! [11]
    //m_tableWidget->setRowCount(3);
    //m_tableWidget->setColumnCount(10);
    //m_tableWidget->setHorizontalHeaderLabels(points);
    //m_tableWidget->setVerticalHeaderLabels(positions);
    m_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //m_tableWidget->setCurrentCell(-1, -1);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //! [11]

    //! [12]
    //for (int point = 0; point < points.size(); ++point) {
    //    for (int position = 0; position < positions.size(); ++position) {
    //        QModelIndex index = m_tableWidget->model()->index(position, point);
    //        m_tableWidget->model()->setData(index, point_val[point][position]);
    //    }
    //}
    //! [12]
}

void GraphDataGenerator::addRow()
{
    m_tableWidget->model()->insertRow(0);
    if (m_tableWidget->model()->rowCount() > m_rowCount)
        m_tableWidget->model()->removeRow(m_rowCount);
    for (int i = 0; i < m_columnCount; i++)
    {
        QModelIndex index = m_tableWidget->model()->index(0, i);
        m_tableWidget->model()->setData(index, ((float)i / (float)m_columnCount) / 2.0f + (float)(QRandomGenerator::global()->bounded(30)) / 100.0f);
    }
    m_tableWidget->resizeColumnsToContents();
}

//! [13]
void GraphDataGenerator::selectFromTable(const QPoint& selection)
{
    m_tableWidget->setFocus();
    //m_tableWidget->setCurrentCell(selection.x(), selection.y());
}
//! [13]

//! [14]
void GraphDataGenerator::selectedFromTable(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousRow)
    Q_UNUSED(previousColumn)
    //m_graph->seriesList().at(0)->setSelectedBar(QPoint(currentRow, currentColumn));
}
//! [14]

void GraphDataGenerator::fixTableSize()
{
    int width = m_tableWidget->horizontalHeader()->length();
    width += m_tableWidget->verticalHeader()->width();
    m_tableWidget->setFixedWidth(width + 2);
    int height = m_tableWidget->verticalHeader()->length();
    height += m_tableWidget->horizontalHeader()->height();
    m_tableWidget->setFixedHeight(height + 2);
}

QVector3D GraphDataGenerator::GetVerticalVector(QVector3D coordinate_x)
{
    const QVector3D tmp(1, 1, 1);
    QVector3D res;
    res.setX(coordinate_x.y() * tmp.z() - coordinate_x.z() * tmp.y());
    res.setY(coordinate_x.z() * tmp.x() - coordinate_x.x() * tmp.z());
    res.setZ(coordinate_x.x() * tmp.y() - coordinate_x.y() * tmp.x());
    return res;
}

void GraphDataGenerator::ModelSetData(std::vector<std::vector<int>>& result)
{
    m_graph->removeCustomItems();
    model->ModelSetData(result);

    float xRange = m_graph->axisX()->max() - m_graph->axisX()->min(),
        yRange = (m_graph->axisY()->max() - m_graph->axisY()->min()) * 2,
        zRange = m_graph->axisZ()->max() - m_graph->axisZ()->min();

    auto iter = result.begin() + 1;
    for (float x0 = result[0][0], y0 = result[0][1], z0 = result[0][2]; iter != result.end(); iter++)
    {
        auto& tmp1 = *iter;
        float x1 = tmp1[0], y1 = tmp1[1], z1 = tmp1[2];
        QCustom3DItem* item = new QCustom3DItem;
        item->setMeshFile(":/img/narrowarrow.obj");
        QImage texture(500, 500, QImage::Format_ARGB32);
        texture.fill(QColorConstants::DarkYellow);
        item->setTextureImage(texture);
        QVector3D dst(x1, y1, z1), src(x0, y0, z0);
        auto direction = QVector3D((x1 - x0) / xRange, (y1 - y0) / yRange, (z0 - z1) / zRange);
        item->setScaling(QVector3D(0.05f, 18 * direction.length() * 0.1f, 0.05f));
        item->setPosition((src + dst) / 2);
        item->setRotation(QQuaternion::rotationTo(QVector3D(0, 1, 0), direction));
        m_graph->addCustomItem(item);
        x0 = x1;
        y0 = y1;
        z0 = z1;
    }
}
