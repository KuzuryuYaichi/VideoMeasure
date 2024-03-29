#ifndef SYNTHESISWIDGET_H
#define SYNTHESISWIDGET_H

#include <QtWidgets/QWidget>
#include <QtDataVisualization/QDataVisualizationGlobal.h>
#include "GraphDataGenerator.h"
#include "CustomTableModel.h"
#include <QTableView>

QT_BEGIN_NAMESPACE_DATAVISUALIZATION
class Q3DBars;
QT_END_NAMESPACE_DATAVISUALIZATION

using namespace QtDataVisualization;

class SynthesisWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SynthesisWidget(QWidget* parent = 0);
    ~SynthesisWidget();
    void ModelSetData(std::vector<std::vector<int>>& result);

private:
    void Synthesis_Setup();

private:
    GraphDataGenerator* generator;
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    CustomTableModel* model;
};

#endif /* SYNTHESISWIDGET_H */
