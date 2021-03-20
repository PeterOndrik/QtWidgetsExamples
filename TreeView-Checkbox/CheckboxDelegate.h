#pragma once
#include <QtWidgets>

class CheckboxDelegate : public QStyledItemDelegate 
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override
    {
        Qt::CheckState last = static_cast<Qt::CheckState>(model->data(index, Qt::CheckStateRole).toInt());
        bool res = QStyledItemDelegate::editorEvent(event, model, option, index);
        Qt::CheckState current = static_cast<Qt::CheckState>(model->data(index, Qt::CheckStateRole).toInt());
        if (last != current)
            Q_EMIT stateChanged(index);
        return  res;
    }
Q_SIGNALS:
    void stateChanged(const QModelIndex& index);
};
