/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "GraphDataGenerator.h"

#define USE_STATIC_DATA

using namespace QtDataVisualization;

GraphDataGenerator::GraphDataGenerator(Q3DBars* bargraph, QTableWidget* tableWidget):
    m_graph(bargraph),
    m_dataTimer(0),
    m_columnCount(100),
    m_rowCount(50),
    m_tableWidget(tableWidget)
{
    //! [5]
    // Set up bar specifications; make the bars as wide as they are deep,
    // and add a small space between them
    m_graph->setBarThickness(1.0f);
    m_graph->setBarSpacing(QSizeF(0.2, 0.2));

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
    //! [6]
    // Set selection mode to slice row
    m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow | QAbstract3DGraph::SelectionSlice);

    //! [6]
#endif

    //! [7]
    // Set theme
    m_graph->activeTheme()->setType(Q3DTheme::ThemeDigia);

    // Set font
    m_graph->activeTheme()->setFont(QFont("Impact", 20));

    // Set preset camera position
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
    //! [7]
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
    m_graph->rowAxis()->setTitle("Y Axis");
    m_graph->rowAxis()->setTitleVisible(true);
    m_graph->columnAxis()->setTitle("X Axis");
    m_graph->columnAxis()->setTitleVisible(true);
    m_graph->valueAxis()->setTitle("Z Axis");
    m_graph->valueAxis()->setTitleVisible(true);
    m_graph->valueAxis()->setLabelFormat("%.1f h");
    //! [10]

    //! [11]
    m_tableWidget->setRowCount(3);
    m_tableWidget->setColumnCount(10);
    m_tableWidget->setHorizontalHeaderLabels(points);
    m_tableWidget->setVerticalHeaderLabels(positions);
    m_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_tableWidget->setCurrentCell(-1, -1);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //! [11]

    //! [12]
    for (int point = 0; point < points.size(); ++point) {
        for (int position = 0; position < positions.size(); ++position) {
            QModelIndex index = m_tableWidget->model()->index(position, point);
            m_tableWidget->model()->setData(index, point_val[point][position]);
        }
    }
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
    m_tableWidget->setCurrentCell(selection.x(), selection.y());
}
//! [13]

//! [14]
void GraphDataGenerator::selectedFromTable(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousRow)
    Q_UNUSED(previousColumn)
    m_graph->seriesList().at(0)->setSelectedBar(QPoint(currentRow, currentColumn));
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
