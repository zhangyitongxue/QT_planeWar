#include "titlescene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    titleScene w;
    w.show();

    return a.exec();
}
