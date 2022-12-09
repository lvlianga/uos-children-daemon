#include "findparent_dialog.h"
#include "../service/define.h"
#include "src/control/config_worker.h"
#include "../service/lock_screen_control.h"
#include "public_method.h"

#include <QVBoxLayout>
#include <QJsonObject>
#include <QKeyEvent>
#include <QWidgetAction>
#include <QAction>
#include <QTimer>
#include <DDesktopEntry>
#include <DFloatingMessage>

using Dtk::Core::DDesktopEntry;

#define CLOSESIZE 40
#define MAPSIZE 32
/**
 * @brief FindParentDialog::FindParentDialog 去找家长对话框
 * @param type 申请的类型
 * @param count 申请的个数
 * @param array 申请的内容
 * @param parent
 * @author lvliang
 * @date 2021-11-10
 */
FindParentDialog::FindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent)
    : DAbstractDialog(parent),
      m_boxlayout(new QVBoxLayout(this)),
      m_closeButton(new DWindowCloseButton(this)),
      m_iconLabel(new QLabel(this)),
      m_textLabel(new QLabel(this)),
      m_icon(new QLabel(this)),
      m_name1(new QLabel(this)),
      m_icon1(new QLabel(this)),
      m_name2(new QLabel(this)),
      m_icon2(new QLabel(this)),
      m_icon3(new QLabel(this)),
      m_icon4(new QLabel(this)),
      labtext(new QLabel(this)),
      m_pushButton1(new DPushButton(this)),
      m_menu(new QMenu(this)),
      m_dtextEdit(new DTextEdit(this)),
      m_pushButton(new DSuggestButton(this)),
      m_username(PublicMethod::getCurrentUsername())
{
    m_listGeneralQuickReply << tr("学习需要，是我们老师推荐的哦！") << tr("今天的作业写完了，我可以放松一下吗？")
                            << tr("刚刚做了家务可以奖励我一下吗~") << tr("没什么理由，就想看看/用一下。");

    m_listEyeExercisesQuickReply << tr("我想要退出这次的健康好习惯") << tr("今天已经做过了，可以不做吗？")
                                 << tr("临时有事需要使用电脑，需要退出这个任务。") << tr("时间间隔太频繁啦~")
                                 << tr("下次再做吧。") << tr("没什么理由，就是想退出。");

    m_listUnLockQuickReply << tr("我想解除今天的电脑使用限制") << tr("今天的作业写完了，我可以放松一下吗？")
                           << tr("临时有事需要使用电脑，需要解除电脑使用限制。") << tr("刚刚做了家务，可以奖励我一下吗~")
                           << tr("学习需要，要用电脑查资料。") << tr("没什么理由，就是想解除。");

    QFont font;
    QPalette pattle;
    pattle.setColor(QPalette::WindowText, labBlack_005);
    font.setWeight(QFont::ExtraLight);

    isSendPushButton = false;

    QHBoxLayout *layout = new QHBoxLayout(m_pushButton1);
    layout->setContentsMargins(10, 0, 0, 0);
    labtext->setText(tr("选择快捷回复"));
    labtext->setFont(font);
    labtext->setPalette(pattle);
    layout->addWidget(labtext, 0, Qt::AlignLeft);

    m_pushButton1->setLayout(layout);
    m_pushButton1->setContentsMargins(0, 0, 0, 0);

    noticeLabel = new QLabel(m_textLabel);
    noticeLabel->setText("0/50");
    setContentsMargins(0, 0, 0, 0);
    initUI();
    setfindParent(type, count, array);
    initConnect();

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool);
}

/**
 * @brief FindParentDialog::setfindParent
 * @param type 请求类型
 * @param count 所有申请应用个数
 * @param array 申请应用内容
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::setfindParent(applyType type, int count, QJsonArray array)
{
    m_count = count;
    m_type = type;
    //数据解析
    dataAnalysis(type, array);
}

/**
 * @brief FindParentDialog::slot_cancelsiginal 取消按钮关闭页面
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::slot_cancelsiginal()
{
    close();
}

/**
 * @brief FindParentDialog::slot_sendsignal 点击去找家长
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::slot_sendsignal()
{
    QString str1;
    if (isSendPushButton) {
        str1 = labtext->text();
    }
    QString str2 = m_dtextEdit->toPlainText();
    setEnable(false);
    QNetworkReply *reply = HttpClient::instance()->sendYouthMsg(m_type, retVal, str1 + str2);
    connect(reply, &QNetworkReply::finished, this, &FindParentDialog::slot_closed);
}

/**
 * @brief FindParentDialog::slot_closed 关闭二维码鉴权界面
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::slot_closed()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(QObject::sender());
    QString result = HttpClient::instance()->checkReply(reply);
    reply->deleteLater();
    QString text;
    //上报成功
    if (!result.isEmpty()) {
        if (HttpClient::instance()->solveJson(result)) {
            QByteArray byteJson =  result.toLocal8Bit();
            QJsonParseError jsonError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(byteJson, &jsonError);
            QJsonObject jsonObj = jsonDoc.object();
            QJsonValue jsonValueResult = jsonObj.value("msg");
            QString msg = jsonValueResult.toString();
            if (msg == "success") {
                text = FindParentDialog::tr("发送成功");
                m_pTips->setIcon(QIcon(OkIcon));
                setshowTips(text);
                QTimer::singleShot(3000, this, [ = ] {
                    this->close();
                });
            } else {
                text = FindParentDialog::tr("网络异常，发送失败");
                m_pTips->setIcon(QIcon(WaringIcon));
                setEnable(true);
                setshowTips(text);
            }
        }
    } else {
        text = FindParentDialog::tr("网络异常，发送失败");
        m_pTips->setIcon(QIcon(WaringIcon));
        setEnable(true);
        setshowTips(text);
        qInfo() << "report failed";
    }
}

/**
 * @brief FindParentDialog::initUI 初始化UI
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::initUI()
{
    m_pTips = new DFloatingMessage(DFloatingMessage::TransientType, this);
    QPalette pe;
    pe.setColor(QPalette::WindowText, toastText);
    m_pTips->setPalette(pe);
    m_pTips->hide();

    setFixedSize(380, 310);

    m_menu->setMinimumWidth(360);

    m_pushButton1->setMenu(m_menu);
    m_pushButton1->setFixedSize(360, 36);

    QFont ft1;
    QPalette palette;
    palette.setColor(QPalette::WindowText, labBlack_085);
    ft1.setWeight(QFont::DemiBold);
    ft1.setPixelSize(13);

    m_textLabel->setText(tr("去找家长"));
    m_textLabel->setPalette(palette);
    m_textLabel->setContentsMargins(4, 0, 0, 0);
    m_textLabel->setFont(ft1);

    QFont ft2;
    QPalette palette1;
    palette1.setColor(QPalette::WindowText, labBlack_085);
    ft2.setWeight(QFont::ExtraLight);
    ft2.setPixelSize(14);

    m_pushButton->setText(tr("发送"));
    m_pushButton->setFont(ft2);
    m_pushButton->setPalette(palette1);

    m_dtextEdit->setFixedSize(360, 88);
    m_dtextEdit->setPlaceholderText(tr("我还想说···"));
    m_dtextEdit->setFontPointSize(14);
    m_dtextEdit->setAcceptRichText(false);
    m_dtextEdit->moveCursor(QTextCursor::Start);
    m_dtextEdit->setContentsMargins(0, 0, 0, 0);

    QWidget *m_mainwidget = new QWidget;

    QHBoxLayout *m_hboxtoplayout = new QHBoxLayout;
    m_hboxtoplayout->setContentsMargins(10, 0, 0, 0);

    m_closeButton->setIconSize(QSize(CLOSESIZE, CLOSESIZE));

    QPixmap pixmap(":/images/light/children-guard-manager.svg");
    QPixmap fitpixmap = pixmap.scaled(MAPSIZE, MAPSIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    m_iconLabel->setPixmap(fitpixmap);
    m_iconLabel->setFixedSize(MAPSIZE, MAPSIZE);

    m_hboxtoplayout->addWidget(m_iconLabel, 0, Qt::AlignBottom | Qt::AlignLeft);
    m_hboxtoplayout->addWidget(m_textLabel, 0, Qt::AlignBottom);
    m_hboxtoplayout->addStretch();
    m_hboxtoplayout->addWidget(m_closeButton, 0, Qt::AlignRight);
    m_mainwidget->setLayout(m_hboxtoplayout);

    QWidget *m_centerwidget = new QWidget;

    m_icon->setContentsMargins(0, 0, 0, 0);
    m_name1->setContentsMargins(0, 0, 0, 0);
    m_icon1->setContentsMargins(0, 0, 0, 0);
    m_name2->setContentsMargins(0, 0, 0, 0);
    m_icon2->setContentsMargins(0, 0, 0, 0);
    m_icon3->setContentsMargins(0, 0, 0, 0);
    m_icon4->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *m_hboxcenterlayout = new QHBoxLayout;
    m_hboxcenterlayout->setContentsMargins(10, 0, 0, 0);
    m_hboxcenterlayout->addWidget(m_icon);
    m_hboxcenterlayout->addWidget(m_name1);
    m_hboxcenterlayout->addWidget(m_icon1);
    m_hboxcenterlayout->addWidget(m_name2);
    m_hboxcenterlayout->addWidget(m_icon2);
    m_hboxcenterlayout->addWidget(m_icon3);
    m_hboxcenterlayout->addWidget(m_icon4);
    m_hboxcenterlayout->addStretch();
    m_icon->hide();
    m_icon1->hide();
    m_name2->hide();
    m_icon2->hide();
    m_icon3->hide();
    m_icon4->hide();
    m_hboxcenterlayout->setContentsMargins(0, 0, 0, 0);
    m_centerwidget->setLayout(m_hboxcenterlayout);
    m_centerwidget->setContentsMargins(10, 0, 0, 0);

    //输入框的打字排班布局
    QVBoxLayout *noticelayout = new QVBoxLayout;
    m_dtextEdit->setLayout(noticelayout);
    noticelayout->addWidget(noticeLabel, 0, Qt::AlignBottom | Qt::AlignRight);

    //最下层发送按钮所在布局
    QVBoxLayout *bottomLayout = new QVBoxLayout;
    bottomLayout->addWidget(m_pushButton, 0, Qt::AlignBottom | Qt::AlignRight);
    bottomLayout->setContentsMargins(0, 0, 10, 10);

    m_pushButton->setFixedSize(88, 36);

    QWidget *bottomwidget = new QWidget;
    bottomwidget->setLayout(bottomLayout);

    m_boxlayout->addWidget(m_mainwidget, 0, Qt::AlignTop);
    m_boxlayout->addSpacing(12);
    m_boxlayout->addWidget(m_centerwidget);
    m_boxlayout->addSpacing(10);
    m_boxlayout->addWidget(m_pushButton1, 0, Qt::AlignCenter);
    m_boxlayout->addSpacing(8);
    m_boxlayout->addWidget(m_dtextEdit, 0, Qt::AlignCenter);

    m_boxlayout->addStretch();
    m_boxlayout->addWidget(bottomwidget, 0, Qt::AlignBottom | Qt::AlignRight);

    m_boxlayout->setContentsMargins(0, 0, 0, 0);

    setLayout(m_boxlayout);
}

/**
 * @brief FindParentDialog::initConnect 初始化信号槽
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::initConnect()
{
    connect(m_closeButton, &DWindowCloseButton::clicked, this, &FindParentDialog::slot_cancelsiginal);
    connect(m_pushButton, &QPushButton::clicked, this, &FindParentDialog::slot_sendsignal);
    connect(m_dtextEdit, &DTextEdit::textChanged, this, [ = ] {
        if (m_dtextEdit->toPlainText().count() > 50)
        {
            noticeLabel->setText("50/50");
            int length = m_dtextEdit->toPlainText().count();
            QString text = m_dtextEdit->toPlainText();
            int position = m_dtextEdit->textCursor().position();//输入后光标原应该在的位置
            QTextCursor text_cursor = m_dtextEdit->textCursor();
            text.remove(position - (length - 50), length - 50); //去除掉多余的文字
            m_dtextEdit->setText(text);
            text_cursor.setPosition(position - (length - 50));
            m_dtextEdit->setTextCursor(text_cursor);
        } else if (m_dtextEdit->toPlainText().count() == 50)
        {
            noticeLabel->setText("50/50");
        } else
        {
            noticeLabel->setText(QString("%1/50").arg(m_dtextEdit->toPlainText().count()));
        }
    });
}

/**
 * @brief FindParentDialog::insertMenuQuickReply 插入快捷回复到菜单
 * @param listQuickReply
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::insertMenuQuickReply(const QStringList &listQuickReply)
{
    //清空菜单
    m_menu->clear();

    //选择回复
    QAction *defaultAction = new QAction(tr("选择快捷回复"), m_menu);
    m_menu->addAction(defaultAction);
    m_menu->setDefaultAction(defaultAction);
    //插入动作
    for (auto it : listQuickReply) {
        QAction *action = new QAction(it, m_menu);
        m_menu->addAction(action);
    }

    //菜单选择
    connect(m_menu, &DMenu::triggered, this, [ & ](QAction * action) {
        labtext->setText(action->text());
        isSendPushButton = (m_menu->defaultAction() != action);
    });
}

/**
 * @brief FindParentDialog::dataAnalysis 根据不同的类型解析对应的数据
 * @param type 鉴权二维码类型
 * @param array 获取的数据内容
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::dataAnalysis(applyType type, QJsonArray array)
{
    //清空数据
    int count = jsonarray.count();
    for (int i = 0; i < count; i++) {
        jsonarray.removeFirst();
    }
    if (type == Install) {
        m_name1->setText(tr("我想下载这") + QString::number(m_count) + tr("个应用: "));
        insertMenuQuickReply(m_listGeneralQuickReply);
        //待安装的应用数组
        sendInstallData(array);
        for (int i = 0; i < (m_count > 4 ? 4 : m_count); i++)  {
            QString appname = array.at(i).toObject().value("app_name").toString();
            QString icon = array.at(i).toObject().value("app_icon").toString();
            setIconAndName(i, icon, appname);
            if (m_count == 1) {
                m_name2->setText(appname);
                m_name2->show();
            }
        }
    } else if (type == ExtendApply) {
        m_name1->setText(tr("我想继续使用应用: "));
        insertMenuQuickReply(m_listGeneralQuickReply);
        //待延长的应用数组
        sendExternData(array);
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
    } else if (type == ApplyBrowser) {
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
    } else if (type == EyeExercises) {
        m_name1->setText(tr("我想退出这次的健康好习惯 "));
        insertMenuQuickReply(m_listEyeExercisesQuickReply);
        QString strJson = ConfigWorker::instance()->getConfigValue(m_username, "EyeCareInterval");
        QJsonObject obj;
        obj.insert("eye_care_interval", strJson.toInt());
        obj.insert("EyeCareGoodHabitId", ConfigWorker::instance()->getConfigValue(m_username, "EyeCareGoodHabitId"));
        jsonarray.append(obj);
    } else if (type == UnLockDesktop) {
        m_name1->setText(tr("我想解锁电脑禁用 "));
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
    }
    QJsonDocument document;
    document.setArray(jsonarray);
    retVal = QString::fromUtf8(document.toJson(QJsonDocument::Compact).constData());
    qInfo() << "retVal==" << retVal.left(20);
}

/**
 * @brief FindParentDialog::setIconAndName 设置图片和名称
 * @param count 个数
 * @param icon 图片
 * @param name 名称
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::setIconAndName(int count, QString icon, QString name)
{
    Q_UNUSED(name)
    QNetworkReply *reply =  HttpClient::instance()->getPictureFromUrl(icon);
    connect(reply, &QNetworkReply::finished, this, [ = ] {
        QPixmap m_avatar;
        // 适应当前设备分辨率
        const auto ratio = devicePixelRatioF();
        QNetworkReply *reply = static_cast<QNetworkReply *>(QObject::sender());

        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray data_bytes = reply->readAll();
            m_avatar.loadFromData(data_bytes);
            m_avatar.scaled(size() * ratio, Qt::KeepAspectRatio, Qt::FastTransformation);
            m_avatar.setDevicePixelRatio(ratio);
            update();
            if (count == 0) {
                m_icon1->setPixmap(m_avatar);
                m_icon1->setScaledContents(true);
                m_icon1->setFixedSize(32, 32);
                m_icon1->show();
            } else if (count == 1) {
                m_icon2->setPixmap(m_avatar);
                m_icon2->setScaledContents(true);
                m_icon2->setFixedSize(32, 32);
                m_icon2->show();
            } else if (count == 2) {
                m_icon3->setPixmap(m_avatar);
                m_icon3->setScaledContents(true);
                m_icon3->setFixedSize(32, 32);
                m_icon3->show();
            } else if (count == 3) {
                m_icon4->setPixmap(m_avatar);
                m_icon4->setScaledContents(true);
                m_icon4->setFixedSize(32, 32);
                m_icon4->show();
            }
        } else
        {
            qWarning() << reply->errorString();
        }
        reply->deleteLater();
    });
}

/**
 * @brief FindParentDialog::setIcon 设置图片
 * @param count 个数
 * @param icon 图片
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::setIcon(int count, QString icon)
{
    QPixmap pixmap;
    pixmap = QIcon::fromTheme(icon).pixmap(48, 48);
    if (count == 0) {
        m_icon1->setPixmap(pixmap);
        m_icon1->setScaledContents(true);
        m_icon1->setFixedSize(32, 32);
        m_icon1->show();
    } else if (count == 1) {
        m_icon2->setPixmap(pixmap);
        m_icon2->setScaledContents(true);
        m_icon2->setFixedSize(32, 32);
        m_icon2->show();
    } else if (count == 2) {
        m_icon3->setPixmap(pixmap);
        m_icon3->setScaledContents(true);
        m_icon3->setFixedSize(32, 32);
        m_icon3->show();
    } else if (count == 3) {
        m_icon4->setPixmap(pixmap);
        m_icon4->setScaledContents(true);
        m_icon4->setFixedSize(32, 32);
        m_icon4->show();
    }
}

/**
 * @brief FindParentDialog::sendInstallData 发送待安装应用数据
 * @param array
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::sendInstallData(QJsonArray array)
{
    for (int i = 0; i < m_count; i++)  {
        QString appname = array.at(i).toObject().value("app_name").toString();
        QString desktop = array.at(i).toObject().value("desktop").toString();
        QString package = array.at(i).toObject().value("deb_name").toString();
        QString icon = array.at(i).toObject().value("app_icon").toString();
        QString version = array.at(i).toObject().value("app_version").toString();
        QString appType = array.at(i).toObject().value("app_type").toString();
        appType = PublicMethod::typeChange(appType);
        int packagemode = array.at(i).toObject().value("package_mode").toInt();

        QJsonObject obj;
        obj.insert("desktop", desktop);
        obj.insert("package", package);
        obj.insert("app_name", appname);
        obj.insert("app_icon", icon);
        obj.insert("app_version", version);
        obj.insert("package_mode", packagemode);
        obj.insert("app_type", appType);
        jsonarray.append(obj);
    }
}

/**
 * @brief FindParentDialog::sendExternData 解析从外部获取的应用内容
 * @param array 所有应用内容
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::sendExternData(QJsonArray array)
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

/**
 * @brief FindParentDialog::setEnable 设置下拉框是否可用
 * @param isEnable true:可用 false:不可用
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::setEnable(bool isEnable)
{
    m_menu->setEnabled(isEnable);
    m_dtextEdit->setEnabled(isEnable);
    m_pushButton->setEnabled(isEnable);
}

/**
 * @brief FindParentDialog::setshowTips 显示提示界面
 * @param text 提示内容
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::setshowTips(const QString &text)
{
    m_pTips->setMessage(text);
    m_pTips->setDuration(3000);
    QFontMetrics m(m_pTips->font());
    m_pTips->setFixedHeight(60);
    m_pTips->setFixedWidth(m.width(text) + 80);
    m_pTips->move((this->width() - m_pTips->width()) / 2, this->height() / 2);
    m_pTips->setWindowFlag(Qt::WindowStaysOnTopHint);
    m_pTips->show();
}

/**
 * @brief FindParentDialog::closeEvent 关闭去找家长界面
 * @param event
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    emit closeMainDialog();
    deleteLater();
}

/**
 * @brief FindParentDialog::keyPressEvent 当点击esc按钮不做任何反应
 * @param event
 * @author lvliang
 * @date 2021-11-10
 */
void FindParentDialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}
