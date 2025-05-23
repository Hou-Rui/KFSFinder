#pragma once
#include <QMainWindow>

class QDockWidget;
class QVBoxLayout;
class QScrollArea;
class KUrlNavigator;
class KFilePlacesView;
class KFilePlacesModel;
class DirOperatorStack;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    QDockWidget* m_toolBarDockWidget;
    QToolBar* m_toolBar;
    KUrlNavigator* m_urlNavigator;
    DirOperatorStack* m_stack;
    QScrollArea* m_scrollArea;

    QDockWidget* m_placesDockWidget;
    KFilePlacesView* m_placesView;
    KFilePlacesModel* m_placesModel;
};