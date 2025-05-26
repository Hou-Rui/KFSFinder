#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QStack>
#include <QUrl>

#include "MainWindow.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("KFSFinder");
    app.setDesktopFileName("org.hourui.kfsfinder.desktop");
    MainWindow mainWindow;
    mainWindow.setObjectName("mainWindow");
    mainWindow.show();
    return app.exec();
}
