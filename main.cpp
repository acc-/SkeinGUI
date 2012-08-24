#include <QtGui/QApplication>
#include "skeingui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SkeinGUI w;

    w.show();
    
    return a.exec();
}
