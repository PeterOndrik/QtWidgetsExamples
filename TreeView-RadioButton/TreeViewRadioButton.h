#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TreeViewRadioButton.h"

class TreeViewRadioButton : public QMainWindow
{
    Q_OBJECT

public:
    TreeViewRadioButton(QWidget *parent = Q_NULLPTR);

private:
    Ui::TreeViewRadioButtonClass ui;
};
