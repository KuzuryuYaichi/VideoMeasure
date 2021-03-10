#ifndef GRAPHDATAGENERATOR_H
#define GRAPHDATAGENERATOR_H

#include <QtDataVisualization/Q3DScatter>
#include <QtDataVisualization/QScatterDataProxy>
#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DScene>
#include <QtDataVisualization/Q3DCamera>
#include <QtDataVisualization/QScatter3DSeries>
#include <QtDataVisualization/Q3DTheme>

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

#include "CustomTableModel.h"

using namespace QtDataVisualization;

class GraphDataGenerator : public QObject
{
public:
    explicit GraphDataGenerator(Q3DScatter* bargraph, QTableView* tableWidget, CustomTableModel* model);
    ~GraphDataGenerator();

    void setupModel();
    void addRow();
    void changeStyle();
    void changePresetCamera();
    void changeTheme();
    void start();
    void selectFromTable(const QPoint& selection);
    void selectedFromTable(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void fixTableSize();
    void ModelSetData(std::vector<std::vector<int>>& result);

private:
    Q3DScatter* m_graph;
    QTimer* m_dataTimer;
    int m_columnCount;
    int m_rowCount;
    QTableView* m_tableWidget;
    CustomTableModel* model;
};

#endif
