#include "CustomTableModel.h"
#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtCore/QRandomGenerator>
#include <QtGui/QColor>

CustomTableModel::CustomTableModel(QObject* parent): QAbstractTableModel(parent)
{
    m_RowCount = 3;
    m_ColumnCount = 10;

    for (int i = 0; i < m_RowCount; i++)
    {
        QVector<qreal>* dataVec = new QVector<qreal>(m_ColumnCount);
        for (int k = 0; k < dataVec->size(); k++)
        {
            dataVec->replace(k, qrand() % 100);
        }
        m_data.append(dataVec);
    }
}

CustomTableModel::~CustomTableModel()
{
    qDeleteAll(m_data);
}

int CustomTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_RowCount;
}

int CustomTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_ColumnCount;
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return QString("%1").arg(section + 1);
    else
    {
        switch (section)
        {
        case 0:return QString("X Axis");
        case 1:return QString("Y Axis"); 
        case 2:return QString("Z Axis");
        }
    }
}

QVariant CustomTableModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return m_data[index.row()]->at(index.column());
    }
    else if (role == Qt::EditRole)
    {
        return m_data[index.row()]->at(index.column());
    }
    else if (role == Qt::BackgroundRole)
    {
        for (const QRect& rect : m_mapping)
        {
            if (rect.contains(index.column(), index.row()))
                return QColor(m_mapping.key(rect));
        }
        return QColor(Qt::white);
    }
    return QVariant();
}

bool CustomTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        m_data[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void CustomTableModel::ModelSetData(std::vector<std::vector<int>>& result)
{
    for (int column = 0; column < m_ColumnCount; ++column)
        for (int row = 0; row < m_RowCount; ++row)
            m_data[row]->replace(column, result[column][row]);
    emit dataChanged(index(0, 0), index(m_RowCount - 1, m_ColumnCount - 1));
}

Qt::ItemFlags CustomTableModel::flags(const QModelIndex& index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void CustomTableModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}
