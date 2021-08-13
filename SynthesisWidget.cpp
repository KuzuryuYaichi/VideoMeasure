#include "SynthesisWidget.h"
#include "GraphDataGenerator.h"

#include <QtDataVisualization/q3dbars.h>
#include <QtDataVisualization/qcategory3daxis.h>
#include <QtDataVisualization/qitemmodelbardataproxy.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/qbar3dseries.h>
#include <QtDataVisualization/q3dtheme.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTableWidget>
#include <QtGui/QScreen>
#include <QtCore/QRandomGenerator>
#include <QtCore/QTimer>
#include <QtGui/QFont>
#include <QtCore/QDebug>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMessageBox>
#include <QItemModelScatterDataProxy>

SynthesisWidget::SynthesisWidget(QWidget* parent): QWidget(parent)
{
    Synthesis_Setup();
}

SynthesisWidget::~SynthesisWidget()
{
    delete generator;
}

void SynthesisWidget::Synthesis_Setup()
{
    MyScatter* graph = new MyScatter();
    QWidget* container = QWidget::createWindowContainer(graph);

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return;
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(screenSize / 2);
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QTableView* tableWidget = new QTableView(this);
    layout->addWidget(container, 1);
    layout->addWidget(tableWidget, 1, Qt::AlignHCenter);

    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    tableWidget->setAlternatingRowColors(true);

    // Since we are dealing with QTableWidget, the model will already have data sorted properly
    // into rows and columns, so we simply set useModelCategories property to true to utilize this.
    QScatterDataProxy* proxy = new QScatterDataProxy();
    model = new CustomTableModel(proxy);
    tableWidget->setModel(model);
    //QItemModelScatterDataProxy* proxy = new QItemModelScatterDataProxy(tableWidget->model(), "X Axis", "Y Axis", "Z Axis");
    QScatter3DSeries* series = new QScatter3DSeries(proxy);
    series->setMesh(QAbstract3DSeries::MeshPyramid);

    QScatterDataArray data;
    for (int i = 0; i < 10; ++i)
        data << QVector3D(i, i, i);
    series->dataProxy()->addItems(data);
    graph->addSeries(series);

    generator = new GraphDataGenerator(graph, tableWidget, model);
    //QObject::connect(series, &QScatter3DSeries::selectedItemChanged, generator, &GraphDataGenerator::selectFromTable);
    //QObject::connect(tableWidget, &QTableWidget::currentCellChanged, generator, &GraphDataGenerator::selectedFromTable);

    generator->start();
}

void SynthesisWidget::ModelSetData(std::vector<std::vector<int>>& result)
{
    generator->ModelSetData(result);
}