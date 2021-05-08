#include "first_try.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    first_try w;
    w.show();
    return a.exec();
}
