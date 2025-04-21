#pragma once
#include <QMainWindow>

class QVBoxLayout;
class QScrollArea;
class KUrlNavigator;
class DirOperatorStack;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    QVBoxLayout* m_layout;
    KUrlNavigator* m_urlNavigator;
    DirOperatorStack* m_stack;
    QScrollArea* m_scrollArea;
};