#ifndef FISHDATASET_H
#define FISHDATASET_H

#include <QtCore/QScopedPointer>
#include <QtCore/QVariantList>

typedef QVariantList FishDataItem;
typedef QList<FishDataItem*> FishDataItemList;

class FishDataSet : public QObject
{
    Q_OBJECT

public:
    explicit FishDataSet();
    ~FishDataSet();

    void clear();

    int addItem(FishDataItem* item);
    int addItems(FishDataItemList* itemList);

    const FishDataItemList& itemList() const;

Q_SIGNALS:
    void itemsAdded(int index, int count);
    void dataCleared();

private:
    FishDataItemList m_variantData;

    Q_DISABLE_COPY(FishDataSet)
};

#endif
