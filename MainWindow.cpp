#include "MainWindow.hpp"
#include "DirOperatorStack.hpp"

#include <KFilePlacesModel>
#include <KFilePlacesView>
#include <KUrlNavigator>
#include <QDir>
#include <QDockWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>
#include <QToolBar>
#include <QUrl>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setObjectName("mainWindow");
    resize(1000, 600);

    m_toolBarDockWidget = new QDockWidget(this);
    m_toolBarDockWidget->setWidget(m_toolBar = new QToolBar());
    m_toolBarDockWidget->setDockLocation(Qt::TopDockWidgetArea);
    m_toolBarDockWidget->setTitleBarWidget(new QWidget());
    m_toolBarDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    m_toolBar->addWidget(m_urlNavigator = new KUrlNavigator());

    m_placesDockWidget = new QDockWidget(this);
    m_placesDockWidget->setWidget(m_placesView = new KFilePlacesView());
    m_placesDockWidget->setDockLocation(Qt::LeftDockWidgetArea);
    m_placesDockWidget->setTitleBarWidget(new QWidget());
    m_placesDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    m_placesView->setModel(m_placesModel = new KFilePlacesModel());
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);

    setCentralWidget(m_scrollArea = new QScrollArea());
    m_scrollArea->setWidget(m_stack = new DirOperatorStack());
    m_scrollArea->setWidgetResizable(true);

    connect(m_placesView, &KFilePlacesView::urlChanged, m_stack, &DirOperatorStack::setUrl, Qt::QueuedConnection);
    connect(m_urlNavigator, &KUrlNavigator::urlChanged, m_stack, &DirOperatorStack::setUrl, Qt::QueuedConnection);
    connect(m_stack, &DirOperatorStack::urlChanged, m_urlNavigator, &KUrlNavigator::setLocationUrl, Qt::QueuedConnection);
    connect(m_stack, &DirOperatorStack::urlChanged, m_placesView, &KFilePlacesView::setUrl, Qt::QueuedConnection);

    auto scrollBar = m_scrollArea->horizontalScrollBar();
    connect(scrollBar, &QScrollBar::rangeChanged, [scrollBar] {
        scrollBar->setValue(scrollBar->maximum());
    });

    m_stack->home();
}