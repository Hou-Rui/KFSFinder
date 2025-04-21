#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QStack>
#include <QUrl>

#include "DirOperator.hpp"
#include "DirOperatorStack.hpp"
#include "MainWindow.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setObjectName("mainWindow");
    mainWindow.show();
    return app.exec();
}
