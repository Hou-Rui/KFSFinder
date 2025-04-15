#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QUrl>
#include <QDebug>
#include <QStack>

#include "DirOperator.hpp"
#include "DirOperatorStack.hpp"
#include "MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setObjectName("mainWindow");
    mainWindow.show();
    return app.exec();
}
