#ifndef APPWHITEFINDPARENTDIALOG_H
#define APPWHITEFINDPARENTDIALOG_H

#include <QWidget>
#include "base_find_parentdialog.h"

class AppWhiteFindParentDialog : public BaseFindParentDialog
{
public:
    explicit AppWhiteFindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent = nullptr);

protected:
    void dataAnalysis(applyType type, QJsonArray array);

private:
    void sendWhiteData(QJsonArray array);

private:
    QStringList m_listGeneralQuickReply;
};

#endif // APPWHITEFINDPARENTDIALOG_H
