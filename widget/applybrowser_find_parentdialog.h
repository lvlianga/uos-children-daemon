#ifndef APPLYBROWSERFINDPARENTDIALOG_H
#define APPLYBROWSERFINDPARENTDIALOG_H

#include <QWidget>
#include "base_find_parentdialog.h"

class ApplyBrowserFindParentDialog : public BaseFindParentDialog
{
public:
    explicit ApplyBrowserFindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent = nullptr);

protected:
    void dataAnalysis(applyType type, QJsonArray array);

private:
    QStringList m_listGeneralQuickReply;
};

#endif // APPLYBROWSERFINDPARENTDIALOG_H
