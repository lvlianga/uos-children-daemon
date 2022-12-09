#ifndef APPEXTERNFINDPARENTDIALOG_H
#define APPEXTERNFINDPARENTDIALOG_H

#include <QWidget>
#include "base_find_parentdialog.h"

class AppExternFindParentDialog : public BaseFindParentDialog
{
public:
    explicit AppExternFindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent = nullptr);

protected:

    virtual void dataAnalysis(applyType type, QJsonArray array);

private:
    void sendExternData(QJsonArray array);

private:

    QStringList m_listGeneralQuickReply;


};

#endif // APPEXTERNFINDPARENTDIALOG_H
