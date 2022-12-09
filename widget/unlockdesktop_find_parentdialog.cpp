#include "unlockdesktop_find_parentdialog.h"
#include "src/control/config_worker.h"

UnLockDesktopFindParentDialog::UnLockDesktopFindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent)
    : BaseFindParentDialog(type, count, array, parent)
{

    m_listUnLockQuickReply << tr("我想解除今天的电脑使用限制") << tr("今天的作业写完了，我可以放松一下吗？")
                           << tr("临时有事需要使用电脑，需要解除电脑使用限制。") << tr("刚刚做了家务，可以奖励我一下吗~")
                           << tr("学习需要，要用电脑查资料。") << tr("没什么理由，就是想解除。");
}

void UnLockDesktopFindParentDialog::dataAnalysis(applyType type, QJsonArray array)
{
    m_name1->setText(tr("我想解除电脑禁用 "));
    insertMenuQuickReply(m_listUnLockQuickReply);
    QString SystemGuardDayOfWeek = ConfigWorker::instance()->getConfigValue(m_username, "SystemGuardDayOfWeek");
    QString startTime = ConfigWorker::instance()->getConfigValue(m_username, "SystemGuardStartTime");
    QString endTime = ConfigWorker::instance()->getConfigValue(m_username, "SystemGuardEndTime");
    QJsonObject obj;
    obj.insert("SystemGuardDayOfWeek", SystemGuardDayOfWeek);
    obj.insert("startTime", startTime);
    obj.insert("endTime", endTime);
    obj.insert("DisableModeId", ConfigWorker::instance()->getConfigValue(m_username, "DisableModeId"));
    jsonarray.append(obj);

    QJsonDocument document;
    document.setArray(jsonarray);
    retVal = QString::fromUtf8(document.toJson(QJsonDocument::Compact).constData());
    qInfo() << "retVal==" << retVal.left(20);
}
