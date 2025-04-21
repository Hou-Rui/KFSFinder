#include "DirOperatorStack.hpp"
#include "DirOperator.hpp"

#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QUrl>

DirOperatorStackItem::DirOperatorStackItem(const QUrl& url, DirOperatorStack* parent)
    : QWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_operator = new DirOperator(url));
    m_layout->addWidget(m_separator = new QFrame());
    m_separator->setFrameShape(QFrame::VLine);
    m_separator->setFrameShadow(QFrame::Sunken);
}

DirOperator* DirOperatorStackItem::dirOperator() const
{
    return m_operator;
}

DirOperatorStack::DirOperatorStack(QWidget* parent)
    : QWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->setAlignment(Qt::AlignLeft);
}

void DirOperatorStack::push(const QUrl& url)
{
    auto item = new DirOperatorStackItem(url, this);
    m_layout->addWidget(item);
    connect(item->dirOperator(), &DirOperator::dirSelected, [this, item](const auto& url) {
        popUntil(item);
        push(url);
    });
    emit dirSelected(url);
}

void DirOperatorStack::home()
{
    clear();
    push(QUrl::fromLocalFile(QDir::homePath()));
}

void DirOperatorStack::pop()
{
    auto op = top();
    if (op == nullptr) {
        return;
    }
    m_layout->removeWidget(op);
    op->deleteLater();
}

void DirOperatorStack::popUntil(DirOperatorStackItem* item)
{
    while (item != top()) {
        pop();
    }
}

DirOperatorStackItem* DirOperatorStack::top() const
{
    int last = m_layout->count() - 1;
    if (auto item = m_layout->itemAt(last)) {
        return static_cast<DirOperatorStackItem*>(item->widget());
    }
    return nullptr;
}

bool DirOperatorStack::isEmpty() const
{
    return m_layout->isEmpty();
}

void DirOperatorStack::selectUrl(const QUrl& url)
{
    while (!isEmpty()) {
        auto op = top()->dirOperator();
        auto option = QUrl::StripTrailingSlash | QUrl::NormalizePathSegments;
        if (url.matches(op->url(), option)) {
            return;
        }
        pop();
    }
    push(url);
}