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
    model = new CustomTableModel;
    QTableView* m_tableView = generator->getTableWidget();
    m_tableView->setModel(model);
}

SynthesisWidget::~SynthesisWidget()
{
    delete generator;
}

QTableView* SynthesisWidget::getTableWidget()
{
    return generator->getTableWidget();
}

void SynthesisWidget::Synthesis_Setup()
{
    Q3DScatter* graph = new Q3DScatter();
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

    //! [1]
    QVBoxLayout* layout = new QVBoxLayout(this);
    QTableView* tableWidget = new QTableView(this);
    layout->addWidget(container, 1);
    layout->addWidget(tableWidget, 1, Qt::AlignHCenter);
    //! [1]

    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    tableWidget->setAlternatingRowColors(true);

    //! [2]
    // Since we are dealing with QTableWidget, the model will already have data sorted properly
    // into rows and columns, so we simply set useModelCategories property to true to utilize this.
    QItemModelBarDataProxy* proxy = new QItemModelBarDataProxy(tableWidget->model());
    proxy->setUseModelCategories(true);
    QScatter3DSeries* series = new QScatter3DSeries(proxy);
    series->setMesh(QAbstract3DSeries::MeshPyramid);
    graph->addSeries(series);
    //! [2]

    //! [3]
    generator = new GraphDataGenerator(graph, tableWidget);
    //QObject::connect(series, &QScatter3DSeries::selectedItemChanged, generator, &GraphDataGenerator::selectFromTable);
    //QObject::connect(tableWidget, &QTableWidget::currentCellChanged, generator, &GraphDataGenerator::selectedFromTable);
    //! [3]

    ////! [4]
    generator->start();
}

void SynthesisWidget::ModelSetData(std::vector<std::vector<int>>& result)
{
    model->ModelSetData(result);
}