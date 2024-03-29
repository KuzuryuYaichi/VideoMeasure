#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include <QScatterDataProxy>
#include "MyVideo.h"

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CustomTableModel(QObject* parent = 0);
    explicit CustomTableModel(QtDataVisualization::QScatterDataProxy* proxy, QObject* parent = 0);
    virtual ~CustomTableModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    void ModelSetData(std::vector<std::vector<int>>& result);
    Qt::ItemFlags flags(const QModelIndex& index) const;

    void addMapping(QString color, QRect area);
    void clearMapping() { m_mapping.clear(); }

private:
    QList<QVector<qreal>*> m_data;
    QHash<QString, QRect> m_mapping;
    int m_ColumnCount, m_RowCount;
    QtDataVisualization::QScatterDataProxy* proxy;
};

#endif // CUSTOMTABLEMODEL_H
