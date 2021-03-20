#pragma once
#include <QtWidgets>

#define RadioButtonRole Qt::UserRole

/*
Source: http://www.wiki.crossplatform.ru/index.php/%D0%9A%D0%B0%D0%BA_%D0%B7%D0%B0%D0%BC%D0%B5%D0%BD%D0%B8%D1%82%D1%8C_checkBox_%D0%BD%D0%B0_radioButton_%D0%B2_QTreeWidget%3F
*/
class RadioButtonDelegate : public QItemDelegate 
{
    Q_OBJECT
public:
    using QItemDelegate::QItemDelegate;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        QString data = index.data(Qt::DisplayRole).toString();
        QRect displayRect, checkRect, textRect, decorationRect;

        QRect rect = option.rect;
        rect.setWidth(option.decorationSize.width());
        displayRect = textRectangle(painter, rect, option.font, data);

        QPixmap pixmap;
        QVariant value = index.data(Qt::DecorationRole);
        if (value.isValid()) {
            pixmap = decoration(option, value);
            decorationRect = QRect(QPoint(0, 0), pixmap.size());
        }

        checkRect = doCheck(option, option.rect, Qt::Checked);
        doLayout(option, &checkRect, &decorationRect, &textRect, false);

        QStyleOptionButton styleOptionButton;
        styleOptionButton.rect = checkRect;
        styleOptionButton.state = option.state;

        if (index.data(Qt::CheckStateRole) == Qt::Checked) {
            styleOptionButton.state |= QStyle::State_On;
            styleOptionButton.state &= ~QStyle::State_Off;
        }
        else {
            styleOptionButton.state |= QStyle::State_Off;
            styleOptionButton.state &= ~QStyle::State_On;
        }

        drawBackground(painter, option, index);
        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorRadioButton, &styleOptionButton, painter);
        drawDisplay(painter, option, textRect, data);
        drawFocus(painter, option, displayRect);
    }

    //bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override
    //{
    //    Qt::CheckState last = static_cast<Qt::CheckState>(model->data(index, Qt::CheckStateRole).toInt());
    //    bool res = QItemDelegate::editorEvent(event, model, option, index);
    //    Qt::CheckState current = static_cast<Qt::CheckState>(model->data(index, Qt::CheckStateRole).toInt());
    //    if (last != current)
    //        Q_EMIT stateChanged(index);
    //    return  res;
    //}

    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override
    {
        if (event->type() == QEvent::MouseButtonRelease) 
        {
            //if (index.data(RadioButtonRole).toBool() && index.flags().testFlag(Qt::ItemIsUserCheckable)) 
            if (index.flags().testFlag(Qt::ItemIsUserCheckable)) 
            {
                QRect checkRect, emptyRect;

                Qt::ItemFlags flags = index.model()->flags(index);
                if (flags.testFlag(Qt::ItemIsUserCheckable))
                    checkRect = doCheck(option, option.rect, Qt::Checked);
                doLayout(option, &checkRect, &emptyRect, &emptyRect, false);

                QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
                if (checkRect.contains(mouse_event->pos())) 
                {
                    bool state = index.data(Qt::CheckStateRole).toBool();
                    if (state == 0) 
                    {
                        model->setData(index, Qt::Checked, Qt::CheckStateRole);

                        QModelIndex parentItem = index.parent();
                        int rowCount = model->rowCount(parentItem);
                        for (int i = 0; i != rowCount; ++i) {
                            QModelIndex child = parentItem.child(i, 0);
                            if (child != index) model->setData(child, Qt::Unchecked, Qt::CheckStateRole);
                        }
                    }
                    return true;
                }
            }
        }
        return QItemDelegate::editorEvent(event, model, option, index);
    }
Q_SIGNALS:
    void stateChanged(const QModelIndex& index);
};
