#include "DirOperatorStack.hpp"
#include "DirOperator.hpp"

#include <QUrl>
#include <QHBoxLayout>
#include <QDebug>

DirOperatorStack::DirOperatorStack(QWidget *parent) : QWidget(parent) {
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->setAlignment(Qt::AlignLeft);
}

void DirOperatorStack::push(const QUrl &url) {
    auto op = new DirOperator(url, this);
    m_layout->addWidget(op);
    connect(op, &DirOperator::dirSelected, this, [this, op](const auto &url) {
        while (op != top()) {
            pop();
        }
        push(url);
    });
    emit dirSelected(url);
}

void DirOperatorStack::home() {
    clear();
    push(QUrl::fromLocalFile(QDir::homePath()));
}

void DirOperatorStack::pop() {
    auto op = top();
    if (op == nullptr) {
        return;
    }
    m_layout->removeWidget(op);
    op->deleteLater();
}

void DirOperatorStack::clear() {
    while (!isEmpty()) {
        pop();
    }
}

DirOperator *DirOperatorStack::top() const {
    auto item = m_layout->itemAt(m_layout->count() - 1);
    if (item == nullptr) {
        return nullptr;
    }
    return qobject_cast<DirOperator *>(item->widget());
}

bool DirOperatorStack::isEmpty() const {
    return m_layout->isEmpty();
}

void DirOperatorStack::selectUrl(const QUrl &url) {
    while (!isEmpty()) {
        auto t = top();
        auto option = QUrl::StripTrailingSlash | QUrl::NormalizePathSegments;
        if (url.matches(t->url(), option)) {
            return;
        }
        pop();
    }
    push(url);
}