#include "MainWindow.hpp"
#include "DirOperatorStack.hpp"

#include <QUrl>
#include <QDir>
#include <QDockWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <KUrlNavigator>
#include <KFilePlacesView>
#include <KFilePlacesModel>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setObjectName("mainWindow");
    resize(1000, 600);
    
    m_placesModel = new KFilePlacesModel(this);
    
    m_placesDockWidget = new QDockWidget(this);
    m_placesDockWidget->setWidget(m_placesView = new KFilePlacesView());
    m_placesDockWidget->setDockLocation(Qt::LeftDockWidgetArea);
    m_placesDockWidget->setTitleBarWidget(new QWidget());
    m_placesDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    m_placesView->setModel(m_placesModel);

    setCentralWidget(new QWidget());
    m_layout = new QVBoxLayout(centralWidget());
    m_layout->addWidget(m_urlNavigator = new KUrlNavigator());
    m_layout->addWidget(m_scrollArea = new QScrollArea());
    m_scrollArea->setWidget(m_stack = new DirOperatorStack());
    m_scrollArea->setWidgetResizable(true);

    connect(m_urlNavigator, &KUrlNavigator::urlChanged, m_stack, &DirOperatorStack::setUrl);
    connect(m_stack, &DirOperatorStack::urlChanged, m_urlNavigator, &KUrlNavigator::setLocationUrl);
    auto scrollBar = m_scrollArea->horizontalScrollBar();
    connect(scrollBar, &QScrollBar::rangeChanged, [scrollBar] {
        scrollBar->setValue(scrollBar->maximum());
    });

    m_stack->home();
}