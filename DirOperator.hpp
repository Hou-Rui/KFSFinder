#pragma once
#include <KDirOperator>

class KFileItem;
class QUrl;
class QWidget;
class QMenu;

class DirOperator : public KDirOperator {
    Q_OBJECT
signals:
    void dirSelected(const QUrl& url);
public:
    DirOperator(const QUrl& urlName = QUrl {}, QWidget* parent = nullptr);
    void selectDir(const KFileItem& item) override;
private slots:
    void _hideHeaderView();
    void _openFile(const QUrl& url);
};