#pragma once
#include <KDirOperator>

class KFileItem;
class QUrl;
class QWidget;

class DirOperator: public KDirOperator {
    Q_OBJECT
signals:
    void dirSelected(const QUrl &url);
public:
    DirOperator(const QUrl &urlName = QUrl{}, QWidget *parent = nullptr);
    void selectDir(const KFileItem &item) override;
private slots:
    void hideHeaderView();
    void openFile(const QUrl &url);
};