#include "DirOperator.hpp"
#include <QUrl>
#include <QTreeView>
#include <KIO/JobUiDelegateFactory>
#include <KIO/OpenUrlJob>
#include <KJobUiDelegate>

DirOperator::DirOperator(const QUrl &urlName, QWidget *parent) : KDirOperator(urlName, parent) {
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setFixedWidth(250);

    setViewMode(KFile::Detail);
    connect(this, &DirOperator::viewChanged, this, &DirOperator::hideHeaderView);
    connect(this, &DirOperator::fileSelected, this, [this](const auto &item) {
        openFile(item.url());
    });
    hideHeaderView();
}

void DirOperator::selectDir(const KFileItem &item) {
    emit dirSelected(item.url());
}

void DirOperator::openFile(const QUrl &url) {
    auto job = new KIO::OpenUrlJob(url, this);
    auto mainWindow = qApp->findChild<QWidget *>("mainWindow");
    KIO::createDefaultJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, mainWindow);
    job->start();
}

void DirOperator::hideHeaderView() {
    auto treeView = qobject_cast<QTreeView *>(view());
    if (treeView != nullptr) {
        treeView->setHeaderHidden(true);
        int columnCount = treeView->model()->columnCount();
        for (int i = 1; i < columnCount; i++) {
            treeView->hideColumn(i);
        }
    }
}
