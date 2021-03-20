#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TreeViewCheckbox.h"

class TreeViewCheckbox : public QMainWindow
{
    Q_OBJECT

public:
    TreeViewCheckbox(QWidget *parent = Q_NULLPTR);

private:
    Ui::TreeViewCheckboxClass ui;
};
