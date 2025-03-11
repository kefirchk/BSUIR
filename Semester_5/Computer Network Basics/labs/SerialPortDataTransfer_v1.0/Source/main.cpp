#include "MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Serial Port Data Transfer 1.0");
    w.setFixedWidth(577);
    w.setFixedHeight(361);
    if(w.getErrorFlag() == true)
        return EXIT_FAILURE;
    w.show();
    return a.exec();
}
