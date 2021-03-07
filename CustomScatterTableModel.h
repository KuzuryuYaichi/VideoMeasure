#ifndef CUSTOMSCATTERTABLEMODEL_H
#define CUSTOMSCATTERTABLEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include "MyVideo.h"

class CustomScatterTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CustomScatterTableModel(QObject* parent = 0);
    virtual ~CustomScatterTableModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    void ModelSetData(std::vector<cv::Point>& result);
    Qt::ItemFlags flags(const QModelIndex& index) const;

    void addMapping(QString color, QRect area);
    void clearMapping() { m_mapping.clear(); }

private:
    QList<QVector<qreal>*> m_data;
    QHash<QString, QRect> m_mapping;
    int m_ColumnCount, m_RowCount;
};

#endif // CUSTOMTABLEMODEL_H