#include "TreeViewRadioButton.h"
#include <QtWidgets>
#include "RadioButtonDelegate.h"

/*
Source: https://stackoverflow.com/questions/56411646/how-to-immediately-detect-checkbox-state-change-in-a-qtreeview
*/
TreeViewRadioButton::TreeViewRadioButton(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QStandardItemModel* model = new QStandardItemModel;
    model->setColumnCount(2);
    for (int i = 0; i < 4; ++i)
    {
        QList<QStandardItem*> l;
        for (int c = 0; c < model->columnCount(); ++c)
        {
            QStandardItem* parent = new QStandardItem(QString("%1-%2").arg(i).arg(c));
            parent->setCheckable(true);
            l << parent;
            for (int j = 0; j < 4; ++j)
            {
                QList<QStandardItem*> ll;
                for (int c = 0; c < model->columnCount(); ++c)
                {
                    QStandardItem* child = new QStandardItem(QString("%1-%2-%3").arg(i).arg(j).arg(c));
                    child->setCheckable(true);
                    ll << child;
                }
                parent->appendRow(ll);
            }
        }
        model->appendRow(l);
    }

    QTreeView* w = new QTreeView;
    w->viewport()->setAttribute(Qt::WA_Hover);
    RadioButtonDelegate* delegate = new RadioButtonDelegate;
    w->setItemDelegate(delegate);
    QObject::connect(delegate, &RadioButtonDelegate::stateChanged, [](const QModelIndex& index)
        {
            QString text = index.data().toString();
            Qt::CheckState state = static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt());
            qDebug() << text << state;
        });
    w->setModel(model);
    w->resize(640, 480);
    w->expandAll();

    this->setCentralWidget(w);
}
