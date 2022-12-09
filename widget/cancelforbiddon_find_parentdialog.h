#ifndef CANCELFORBIDDONFINDPARENTDIALOG_H
#define CANCELFORBIDDONFINDPARENTDIALOG_H

#include <QWidget>
#include "base_find_parentdialog.h"

class CancelForbiddonFindParentDialog : public BaseFindParentDialog
{
public:
    explicit CancelForbiddonFindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent = nullptr);

protected:
    void dataAnalysis(applyType type, QJsonArray array);

private:
    void sendcancelForbiddonData(QJsonArray array);

private:
    QStringList m_listGeneralQuickReply;
};

#endif // CANCELFORBIDDONFINDPARENTDIALOG_H
