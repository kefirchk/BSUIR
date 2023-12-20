#include "mainwindow.h"
#include <QApplication>
#include <QScreen>


int main(int argc, char *argv[])   //главная функция
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("IdeaBank");
    w.resize(706, 582);
    w.show();




//    QScreen *screen = QGuiApplication::primaryScreen();
//    QPixmap screenshot = screen->grabWindow(0);
//    screenshot.save("screenshot.png");






    return a.exec();
}
