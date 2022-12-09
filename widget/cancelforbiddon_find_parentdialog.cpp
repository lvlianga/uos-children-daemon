#include "cancelforbiddon_find_parentdialog.h"
#include <DDesktopEntry>

using Dtk::Core::DDesktopEntry;

CancelForbiddonFindParentDialog::CancelForbiddonFindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent)
    : BaseFindParentDialog(type, count, array, parent)
{
    m_listGeneralQuickReply << tr("学习需要，是我们老师推荐的哦！") << tr("今天的作业写完了，我可以放松一下吗？")
                            << tr("刚刚做了家务可以奖励我一下吗~") << tr("没什么理由，就想看看/用一下。");
}

void CancelForbiddonFindParentDialog::dataAnalysis(applyType type, QJsonArray array)
{
    m_name1->setText(tr("我想使用: "));
    insertMenuQuickReply(m_listGeneralQuickReply);
    //待延长的应用数组
    sendcancelForbiddonData(array);
    for (int i = 0; i < (m_count > 4 ? 4 : m_count); i++)  {
        QString desktop = array.at(i).toObject().value("desktop").toString();
        QString name = "/usr/share/applications/" + desktop;
        DDesktopEntry desktops(name);
        QString m_name = desktops.name();
        QString m_genericName = desktops.genericName();
        QString nLocalKey = QString("Name[%1]").arg(QLocale::system().name());
        QString m_localName;
        m_localName = desktops.stringValue(nLocalKey, "Desktop Entry", m_name);
        QString icon1;
        icon1 = desktops.stringValue("Icon");
        if (m_genericName != "" && (desktops.stringValue("X-Deepin-Vendor") == QStringLiteral("deepin"))) {
            m_localName = m_genericName;
        }
        if (m_count == 1) {
            m_name2->setText(m_localName);
            m_name2->show();
        }
        setIcon(i, icon1);
    }
    QJsonDocument document;
    document.setArray(jsonarray);
    retVal = QString::fromUtf8(document.toJson(QJsonDocument::Compact).constData());
    qInfo() << "retVal==" << retVal.left(20);
}

void CancelForbiddonFindParentDialog::sendcancelForbiddonData(QJsonArray array)
{
    for (int i = 0; i < m_count; i++)  {
        QString appname = array.at(i).toObject().value("app_name").toString();
        QString desktop = array.at(i).toObject().value("desktop").toString();
        QString package = array.at(i).toObject().value("package").toString();
        QString icon = array.at(i).toObject().value("app_icon").toString();
        int packagemode = array.at(i).toObject().value("package_mode").toInt();
        QString valid_date = array.at(i).toObject().value("valid_date").toString();
        QString name = "/usr/share/applications/" + desktop;
        DDesktopEntry desktops(name);
        QString m_name = desktops.name();
        QString m_genericName = desktops.genericName();
        QString nLocalKey = QString("Name[%1]").arg(QLocale::system().name());
        QString m_localName;
        m_localName = desktops.stringValue(nLocalKey, "Desktop Entry", m_name);
        QString icon1;
        icon1 = desktops.stringValue("Icon");
        if (m_genericName != "" && (desktops.stringValue("X-Deepin-Vendor") == QStringLiteral("deepin"))) {
            m_localName = m_genericName;
        }
        appname = m_localName;
        QJsonObject obj;
        obj.insert("desktop", desktop);
        obj.insert("package", package);
        obj.insert("app_name", appname);
        obj.insert("app_icon", icon1);
        obj.insert("package_mode", packagemode);
        obj.insert("valid_date", valid_date);
        jsonarray.append(obj);
    }
}
