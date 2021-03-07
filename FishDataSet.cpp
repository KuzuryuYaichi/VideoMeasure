#include "FishDataSet.h"

FishDataSet::FishDataSet(): QObject(0)
{
}

FishDataSet::~FishDataSet()
{
    clear();
}

void FishDataSet::clear()
{
    foreach(FishDataItem* item, m_variantData)
    {
        item->clear();
        delete item;
    }
    m_variantData.clear();
    emit dataCleared();
}

int FishDataSet::addItem(FishDataItem* item)
{
    m_variantData.append(item);
    int addIndex = m_variantData.size();

    emit itemsAdded(addIndex, 1);
    return addIndex;
}

int FishDataSet::addItems(FishDataItemList* itemList)
{
    int newCount = itemList->size();
    int addIndex = m_variantData.size();
    m_variantData.append(*itemList);
    delete itemList;
    emit itemsAdded(addIndex, newCount);
    return addIndex;
}

const FishDataItemList& FishDataSet::itemList() const
{
    return m_variantData;
}
