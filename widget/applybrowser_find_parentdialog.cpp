#include "applybrowser_find_parentdialog.h"
#include "src/control/config_worker.h"
#include "../service/define.h"

ApplyBrowserFindParentDialog::ApplyBrowserFindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent)
    : BaseFindParentDialog(type, count, array, parent)
{
    m_listGeneralQuickReply << tr("今天的作业做完了，我可以放松一下吗？") << tr("刚刚完成了家务，可以奖励我一下吗？")
                            << tr("学习需要，是老师推荐的。") << tr("没什么理由，就想看看/用一下。");
}

void ApplyBrowserFindParentDialog::dataAnalysis(applyType type, QJsonArray array)
{
    //获取网站地址
    QString urls = array.at(0).toString().section('/', 0, 2);
    QString NetWhiteUrlList = ConfigWorker::instance()->getConfigValue(m_username, "NetWhiteUrlList");
    QByteArray byteJson = NetWhiteUrlList.toLocal8Bit();
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteJson, &jsonError);
    QJsonArray jsonarraymain = jsonDoc.object().value("urlList").toArray();
    int url_id = -1;
    QString cmd = "Add";
    for (int i = 1; i < jsonarraymain.count(); i++) {
        if (urls == jsonarraymain.at(i).toObject().value("url").toString()) {
            cmd = "Update";
            url_id = jsonarraymain.at(i).toObject().value("url_id").toInt();
        }
    }
    QJsonObject obj;
    obj.insert("url", urls);
    obj.insert("cmd", cmd);
    obj.insert("url_id", url_id);

    jsonarray.append(obj);

    m_icon->setPixmap(network_2x);
    m_icon->setFixedSize(30, 24);
    m_icon->setScaledContents(true);
    m_icon->show();
    m_name1->setText(tr("我想看看: "));
    insertMenuQuickReply(m_listGeneralQuickReply);
    QFont font1;
    QPalette pattle1;
    pattle1.setColor(QPalette::WindowText, QColor(QRgb(qRgba(0, 128, 255, 1))));
    font1.setUnderline(true);
    m_name2->setFont(font1);
    m_name2->setPalette(pattle1);
    QFontMetrics fontwidth(m_name2->font());
    QString m_urls = fontwidth.elidedText(urls, Qt::ElideMiddle, 250);
    m_name2->setText(m_urls);
    m_name2->show();

    QJsonDocument document;
    document.setArray(jsonarray);
    retVal = QString::fromUtf8(document.toJson(QJsonDocument::Compact).constData());
    qInfo() << "retVal==" << retVal;
}
