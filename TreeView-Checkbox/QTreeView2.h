#pragma once

#include <QTreeView>
#include <QMouseEvent>
#include <QDebug>
#include <QStandardItem>

class QTreeView2 : public QTreeView 
{
public:
    QTreeView2(QWidget* parent = 0) : QTreeView(parent) {}
    virtual ~QTreeView2() {}

protected:
    void resettingCheckBox(QModelIndex& parentIndex) 
    {
        if (!parentIndex.isValid())
            return;

        QString text = parentIndex.data(Qt::DisplayRole).value<QString>();
        qDebug() << "parent is: " << text;

        if (model()->hasChildren(parentIndex)) {
            for (int i = 0; i < model()->rowCount(parentIndex); i++) 
            {
                QModelIndex childIndex = model()->index(i, 0, parentIndex);

                if (model()->hasChildren(childIndex))
                    resettingCheckBox(childIndex);
                else 
                {
                    QString text = childIndex.data(Qt::DisplayRole).value<QString>();
                    qDebug() << "child is: " << text;

                    QStandardItem* parentItem = static_cast<QStandardItem*> (parentIndex.internalPointer());
                    QStandardItem* childItem = static_cast<QStandardItem*> (childIndex.internalPointer());

                    if (parentItem->checkState() == Qt::Checked) {
                        qDebug() << "child item " << childItem->checkState();
                        childItem->setCheckState(Qt::Unchecked);

                    }
                    else {
                        qDebug() << "child item " << childItem->checkState();
                        childItem->setCheckState(Qt::Checked);
                    }
                }
            }
        }
    }

    void mousePressEvent(QMouseEvent* event) {
        QModelIndex index = indexAt(event->pos());

        if (index.isValid()) {
            QStyleOptionButton opt;
            opt.QStyleOption::operator=(viewOptions());
            opt.rect = visualRect(index);
            QRect rect = style()->subElementRect(QStyle::SE_ViewItemCheckIndicator, &opt);

            if (rect.contains(event->pos())) {
                resettingCheckBox(index);
            }

            QTreeView::mousePressEvent(event);
        }
    }
};
