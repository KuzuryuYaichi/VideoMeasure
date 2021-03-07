#ifndef FISHDATASET_H
#define FISHDATASET_H

#include <QtCore/QScopedPointer>
#include <QtCore/QVariantList>

//! [1]
typedef QVariantList FishDataItem;
typedef QList<FishDataItem*> FishDataItemList;
//! [1]

class FishDataSet : public QObject
{
    Q_OBJECT

public:
    explicit FishDataSet();
    ~FishDataSet();

    //! [0]
    void clear();

    int addItem(FishDataItem* item);
    int addItems(FishDataItemList* itemList);

    const FishDataItemList& itemList() const;

Q_SIGNALS:
    void itemsAdded(int index, int count);
    void dataCleared();
    //! [0]

private:
    FishDataItemList m_variantData;

    Q_DISABLE_COPY(FishDataSet)
};

#endif
