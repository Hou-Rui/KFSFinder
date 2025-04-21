#include "MainWindow.hpp"
#include "DirOperatorStack.hpp"

#include <QUrl>
#include <QDir>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <KUrlNavigator>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setObjectName("mainWindow");
    resize(800, 600);

    setCentralWidget(new QWidget());
    m_layout = new QVBoxLayout(centralWidget());
    m_layout->addWidget(m_urlNavigator = new KUrlNavigator());
    m_layout->addWidget(m_scrollArea = new QScrollArea());
    m_scrollArea->setWidget(m_stack = new DirOperatorStack());
    m_scrollArea->setWidgetResizable(true);

    connect(m_urlNavigator, &KUrlNavigator::urlChanged, m_stack, &DirOperatorStack::selectUrl);
    connect(m_stack, &DirOperatorStack::dirSelected, m_urlNavigator, &KUrlNavigator::setLocationUrl);
    auto scrollBar = m_scrollArea->horizontalScrollBar();
    connect(scrollBar, &QScrollBar::rangeChanged, [scrollBar] {
        scrollBar->setValue(scrollBar->maximum());
    });

    m_stack->home();
}