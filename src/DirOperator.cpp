#include "DirOperator.hpp"
#include <KIO/JobUiDelegateFactory>
#include <KIO/OpenUrlJob>
#include <KJobUiDelegate>
#include <QMenu>
#include <QTreeView>
#include <QUrl>

DirOperator::DirOperator(const QUrl& urlName, QWidget* parent)
    : KDirOperator(urlName, parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setFixedWidth(250);
    setViewMode(KFile::Detail);
    showOpenWithActions(true);

    connect(this, &DirOperator::viewChanged, [this] {
        _hideHeaderView();
    });
    connect(this, &DirOperator::fileSelected, [this](const auto& item) {
        _openFile(item.url());
    });
    connect(this, &DirOperator::contextMenuAboutToShow, [this](const auto& item, QMenu* menu) {
        menu->removeAction(action(OpenContainingFolder));
    });
    _hideHeaderView();
}

void DirOperator::selectDir(const KFileItem& item)
{
    emit dirSelected(item.url());
}

void DirOperator::_openFile(const QUrl& url)
{
    auto job = new KIO::OpenUrlJob(url, this);
    auto mainWindow = qApp->findChild<QWidget*>("mainWindow");
    KIO::createDefaultJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, mainWindow);
    job->start();
}

void DirOperator::_hideHeaderView()
{
    auto treeView = qobject_cast<QTreeView*>(view());
    if (treeView != nullptr) {
        treeView->setHeaderHidden(true);
        int columnCount = treeView->model()->columnCount();
        for (int i = 1; i < columnCount; i++) {
            treeView->hideColumn(i);
        }
    }
}
