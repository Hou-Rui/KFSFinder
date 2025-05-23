#pragma once
#include <QWidget>

class QFrame;
class QUrl;
class QHBoxLayout;
class DirOperator;
class DirOperatorStackItem;

class DirOperatorStack : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)

signals:
    void urlChanged(const QUrl& url);

public:
    explicit DirOperatorStack(QWidget* parent = nullptr);
    void push(const QUrl& url);
    void home();
    void pop();
    void popUntil(DirOperatorStackItem* item);
    inline void clear() { popUntil(nullptr); }
    DirOperatorStackItem* top() const;
    bool isEmpty() const;
    QUrl url() const;
public slots:
    void setUrl(const QUrl& url);

private:
    QHBoxLayout* m_layout;
};

class DirOperatorStackItem : public QWidget {
    Q_OBJECT
public:
    explicit DirOperatorStackItem(const QUrl& url, DirOperatorStack* parent = nullptr);
    DirOperator* dirOperator() const;

private:
    QHBoxLayout* m_layout;
    DirOperator* m_operator;
    QFrame* m_separator;
};