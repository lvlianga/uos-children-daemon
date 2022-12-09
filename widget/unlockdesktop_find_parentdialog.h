#ifndef UNLOCKDESKTOPFINDPARENTDIALOG_H
#define UNLOCKDESKTOPFINDPARENTDIALOG_H

#include <QWidget>
#include "base_find_parentdialog.h"

class UnLockDesktopFindParentDialog : public BaseFindParentDialog
{
public:
    explicit UnLockDesktopFindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent = nullptr);

protected:
    void dataAnalysis(applyType type, QJsonArray array);

private:
    QStringList m_listUnLockQuickReply;
};

#endif // UNLOCKDESKTOPFINDPARENTDIALOG_H
