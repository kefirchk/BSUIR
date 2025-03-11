#include "MainWindow.h"

#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Serial Port Data Transfer 3.0");
    w.setFixedHeight(360);
    if(w.getErrorFlag() == true)
        return EXIT_FAILURE;
    w.show();
    return a.exec();
}
