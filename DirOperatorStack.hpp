#pragma once
#include <QWidget>

class QUrl;
class QHBoxLayout;
class DirOperator;

class DirOperatorStack: public QWidget {
    Q_OBJECT
signals:
    void dirSelected(const QUrl &url);
public:
    explicit DirOperatorStack(QWidget *parent = nullptr);
    void push(const QUrl &url);
    void home();
    void pop();
    void clear();
    DirOperator *top() const;
    bool isEmpty() const;
public slots:
    void selectUrl(const QUrl &url);
private:
    QHBoxLayout *m_layout;
};