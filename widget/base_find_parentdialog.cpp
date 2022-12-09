#include "base_find_parentdialog.h"
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

BaseFindParentDialog::BaseFindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent)
    : DAbstractDialog(parent)
    , m_boxlayout(new QVBoxLayout(this))
    , m_closeButton(new DWindowCloseButton(this))
    , m_iconLabel(new QLabel(this))
    , m_textLabel(new QLabel(this))
    , m_icon(new QLabel(this))
    , m_name1(new QLabel(this))
    , m_icon1(new QLabel(this))
    , m_name2(new QLabel(this))
    , m_icon2(new QLabel(this))
    , m_icon3(new QLabel(this))
    , m_icon4(new QLabel(this))
    , labtext(new QLabel(this))
    , m_pushButton1(new DPushButton(this))
    , m_menu(new QMenu(this))
    , m_dtextEdit(new DTextEdit(this))
    , m_pushButton(new DSuggestButton(this))
    , m_type(type)
    , m_count(count)
    , m_array(array)
    , m_username(PublicMethod::getCurrentUsername())
{
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
    initConnect();

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool);
}

void BaseFindParentDialog::initUI()
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

    m_hboxtoplayout->addWidget(m_iconLabel, 0, Qt::AlignCenter | Qt::AlignLeft);
    m_hboxtoplayout->addWidget(m_textLabel, 0, Qt::AlignCenter);
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

    dataAnalysis(m_type, m_array);
}

void BaseFindParentDialog::initConnect()
{
    connect(m_closeButton, &DWindowCloseButton::clicked, this, &BaseFindParentDialog::close);
    connect(m_pushButton, &QPushButton::clicked, this, &BaseFindParentDialog::slot_sendsignal);
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

void BaseFindParentDialog::setEnable(bool isEnable)
{
    m_menu->setEnabled(isEnable);
    m_dtextEdit->setEnabled(isEnable);
    m_pushButton->setEnabled(isEnable);
}

void BaseFindParentDialog::slot_sendsignal()
{
    QString str1;
    if (isSendPushButton) {
        str1 = labtext->text();
    }
    QString str2 = m_dtextEdit->toPlainText();
    setEnable(false);
    QNetworkReply *reply = HttpClient::instance()->sendYouthMsg(m_type, retVal, str1 + str2);
    connect(reply, &QNetworkReply::finished, this, &BaseFindParentDialog::slot_closed);
}

void BaseFindParentDialog::slot_closed()
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
                text = BaseFindParentDialog::tr("发送成功");
                m_pTips->setIcon(QIcon(OkIcon));
                setshowTips(text);
                QTimer::singleShot(3000, this, [ = ] {
                    this->close();
                });
            } else {
                text = BaseFindParentDialog::tr("网络异常，发送失败");
                m_pTips->setIcon(QIcon(WaringIcon));
                setEnable(true);
                setshowTips(text);
            }
        }
    } else {
        text = BaseFindParentDialog::tr("网络异常，发送失败");
        m_pTips->setIcon(QIcon(WaringIcon));
        setEnable(true);
        setshowTips(text);
        qInfo() << "report failed";
    }
}

/**
 * @brief FindParentDialog::setshowTips 显示提示界面
 * @param text 提示内容
 * @author lvliang
 * @date 2021-11-10
 */
void BaseFindParentDialog::setshowTips(const QString &text)
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

void BaseFindParentDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    emit closeMainDialog();
    deleteLater();
}

void BaseFindParentDialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

/**
 * @brief FindParentDialog::insertMenuQuickReply 插入快捷回复到菜单
 * @param listQuickReply
 * @author lvliang
 * @date 2021-11-10
 */
void BaseFindParentDialog::insertMenuQuickReply(const QStringList &listQuickReply)
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
 * @brief FindParentDialog::setIcon 设置图片
 * @param count 个数
 * @param icon 图片
 * @author lvliang
 * @date 2021-11-10
 */
void BaseFindParentDialog::setIcon(int count, QString icon)
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
