#include "TreeViewCheckbox.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TreeViewCheckbox w;
    w.show();
    return a.exec();
}
