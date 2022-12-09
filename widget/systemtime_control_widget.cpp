#include "systemtime_control_widget.h"

#include <DLabel>
#include <DCommandLinkButton>

#include <QFrame>
#include <QApplication>
#include <QDesktopWidget>
#include <QLayout>
#include <QTimer>
#include <QCloseEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGraphicsBlurEffect>

static SystemTimeControlWidget *g_systemTimeControlWidget = nullptr;

WhiteDialog::WhiteDialog(QWidget *parent)
    : DAbstractDialog(parent)
{
    // TODO dailog圆角目前和UI设计不符，后面可改
    QPalette pa;
    pa.setColor(QPalette::Background, Qt::white);

    QFrame *frame = new QFrame(this);
    frame->setFixedSize(460, 360);
    frame->setPalette(pa);
    frame->setAutoFillBackground(true);

    DLabel *picLabel = new DLabel(this);
    picLabel->setFixedSize(300, 190);
    picLabel->setScaledContents(true);
    picLabel->setPixmap(QPixmap(":/images/light/overtime.png"));
    QHBoxLayout *picLabelLayout = new QHBoxLayout;
    picLabelLayout->addStretch();
    picLabelLayout->addWidget(picLabel);
    picLabelLayout->addStretch();

    QFont font1("NotoSansCJKsc");
    font1.setPixelSize(15);
    font1.setWeight(QFont::DemiBold);

    QFont font2("NotoSansCJKsc");
    font2.setPixelSize(13);
    font2.setWeight(QFont::Normal);

    DLabel *textLabel = new DLabel(this);
    textLabel->setMinimumSize(240, 22);
    textLabel->setText(tr("根据家长设置，现已到电脑禁用时段"));
    textLabel->setFont(font1);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setWordWrap(true);
    QHBoxLayout *textLabelLayout = new QHBoxLayout;
    textLabelLayout->addWidget(textLabel, 0, Qt::AlignHCenter);

    DCommandLinkButton *btn = new DCommandLinkButton(tr("家长解锁"), this);
    btn->setMinimumSize(52, 19);
    btn->setFont(font2);
    connect(btn, &DCommandLinkButton::clicked, this, &WhiteDialog::sigParentUnlock);
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(btn, 0, Qt::AlignHCenter);

    QVBoxLayout *frameLayout = new QVBoxLayout;
    frameLayout->setContentsMargins(0, 30, 0, 40);
    frameLayout->setSpacing(0);
    frameLayout->addLayout(picLabelLayout);
    frameLayout->addSpacing(40);
    frameLayout->addLayout(textLabelLayout);
    frameLayout->addSpacing(8);
    frameLayout->addLayout(btnLayout);
    frameLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(frameLayout);
    mainLayout->addStretch();
}

WhiteDialog::~WhiteDialog()
{

}

void WhiteDialog::showWindow()
{
    showstatus = true;
    show();
}

void WhiteDialog::closeWindow()
{
    showstatus = false;
    close();
}

void WhiteDialog::focusOutEvent(QFocusEvent *e)
{
    Q_UNUSED(e);

    activateWindow(); // 失去焦点之后将窗口置顶
}

void WhiteDialog::closeEvent(QCloseEvent *event)
{
    if (showstatus) {
        event->ignore();
    } else {
        event->accept();
    }
}

void WhiteDialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        break;
    case Qt::Key_Shift:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

void WhiteDialog::licenseWin()
{
    //获取dock栏上各个应用程序图标所对应的各自的dbus接口
    m_pWm = new  WM("com.deepin.wm", "/com/deepin/wm", QDBusConnection::sessionBus());
    m_currentWorkspace = m_pWm->GetCurrentWorkspace();
    connect(m_pWm, &WM::workspaceCountChanged, [ = ](int count) {
        Q_UNUSED(count);
        m_pWm->SetCurrentWorkspace(m_currentWorkspace);
    });

}

SystemTimeControlWidget::SystemTimeControlWidget(QWidget *parent)
    : DWidget(parent),
      graphicEffect(new QGraphicsBlurEffect)
{
    graphicEffect->setBlurRadius(30);
    graphicEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);
    setGraphicsEffect(graphicEffect);

    setWindowOpacity(0.7); // 设置透明度
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool); // 屏蔽按钮  置顶  dock栏不显示应用图标(会使程序无法结束)

    //根据屏幕大小设置界面大小
    //获取主屏幕分辨率
    QRect screenRect = QApplication::desktop()->screenGeometry();
    resize(screenRect.size()); // 全屏大小

    m_dialog = new WhiteDialog(this);
    m_dialog->setFixedSize(460, 360);
    m_dialog->moveToCenter(); // 移动到中间
    connect(m_dialog, &WhiteDialog::sigParentUnlock, this, &SystemTimeControlWidget::sigParentUnlock);

    m_keybindInter = new KeybingdingInter("com.deepin.daemon.Keybinding",
                                          "/com/deepin/daemon/Keybinding",
                                          QDBusConnection::sessionBus(), this);

    //super launcher
    m_launcher = queryKeyBind("launcher", 0);
    m_keybindInter->Reset();
}

QString SystemTimeControlWidget::queryKeyBind(const QString &id, int type)
{
    //preview-workspace
    QDBusPendingReply<QString> reply = m_keybindInter->Query(id, type);
    QString  shortcut = reply.argumentAt<0>();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(shortcut.toLocal8Bit().data());
    QJsonObject jsonObject = jsonDocument.object();
    QString accels = jsonObject.value("Accels").toArray().at(0).toString();
    return accels;
}

void SystemTimeControlWidget::setKeyBind(const QString &id, int type, const QString &keystroke)
{
    m_keybindInter->AddShortcutKeystroke(id, type, keystroke);
}

void SystemTimeControlWidget::setAllKeyEmpty()
{
    m_keybindInter->ClearShortcutKeystrokes("move-to-workspace-left", 3);
    m_keybindInter->ClearShortcutKeystrokes("move-to-workspace-right", 3);
    m_keybindInter->ClearShortcutKeystrokes("preview-workspace", 3);
    m_keybindInter->ClearShortcutKeystrokes("expose-windows", 3);
    m_keybindInter->ClearShortcutKeystrokes("expose-all-windows", 3);
    m_keybindInter->ClearShortcutKeystrokes("activate-window-menu", 3);
    m_keybindInter->ClearShortcutKeystrokes("launcher", 0);
}

void SystemTimeControlWidget::setLastKey()
{
    setKeyBind("move-to-workspace-left", 3, m_moveToWorkspaceLeft);
    setKeyBind("move-to-workspace-right", 3, m_moveToWorkspaceRight);
    setKeyBind("preview-workspace", 3, m_previewWorkspace);
    setKeyBind("expose-windows", 3, m_exposeWindows);
    setKeyBind("expose-all-windows", 3, m_exposeAllWindows);
    setKeyBind("activate-window-menu", 3, m_activateWindowMenu);
    setKeyBind("launcher", 0, m_launcher);
}

xcb_atom_t SystemTimeControlWidget::internAtom(const char *name, bool only_if_exists)
{
    return internAtom(QX11Info::connection(), name, only_if_exists);
}

xcb_atom_t SystemTimeControlWidget::internAtom(xcb_connection_t *connection, const char *name, bool only_if_exists)
{
    if (!name || *name == 0)
        return  XCB_NONE;

    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(connection, only_if_exists, strlen(name), name);
    xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(connection, cookie, 0);

    if (!reply)
        return XCB_NONE;

    xcb_atom_t atom = reply->atom;
    free(reply);

    return atom;
}

void SystemTimeControlWidget::sendWindowMove(quint32 WId, int desktop)
{
    xcb_client_message_event_t xev;

    xev.response_type = XCB_CLIENT_MESSAGE;
    xev.type = internAtom("_NET_NUMBER_OF_DESKTOPS");
    xev.window = WId;
    xev.format = 32;
    xev.data.data32[0] = desktop;
    xev.data.data32[1] = 0;
    xev.data.data32[2] = 0;
    xev.data.data32[3] = 0;
    xev.data.data32[4] = 0;

    xcb_send_event(QX11Info::connection(), false, QX11Info::appRootWindow(QX11Info::appScreen()),
                   XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY,
                   (const char *)&xev);

    xcb_flush(QX11Info::connection());
}

SystemTimeControlWidget *SystemTimeControlWidget::instance()
{
    if (g_systemTimeControlWidget == nullptr) {
        g_systemTimeControlWidget = new SystemTimeControlWidget;
    }

    return g_systemTimeControlWidget;
}

SystemTimeControlWidget::~SystemTimeControlWidget()
{

}

void SystemTimeControlWidget::showWidget()
{
    sendWindowMove(this->winId(), 1);
    showFullScreen();
    m_dialog->showWindow();
    showstatus = true;
    //super shift left  move-to-workspace-left
    m_moveToWorkspaceLeft = queryKeyBind("move-to-workspace-left", 3);
    //super shift right  move-to-workspace-right
    m_moveToWorkspaceRight = queryKeyBind("move-to-workspace-right", 3);
    //super s preview-workspace
    m_previewWorkspace = queryKeyBind("preview-workspace", 3);
    //super expose-windows
    m_exposeWindows = queryKeyBind("expose-windows", 3);
    //super a expose-all-windows
    m_exposeAllWindows = queryKeyBind("expose-all-windows", 3);
    //alt space activate-window-menu
    m_activateWindowMenu = queryKeyBind("activate-window-menu", 3);
    //super launcher
    m_launcher = queryKeyBind("launcher", 0);
    setAllKeyEmpty();
//    qInfo() << m_moveToWorkspaceLeft << m_moveToWorkspaceRight << m_previewWorkspace
//            << m_exposeWindows << m_exposeAllWindows << m_launcher;
//    qInfo() << "showWidget showstatus is " << showstatus;
}

void SystemTimeControlWidget::closeWidget()
{
    showstatus = false;
    // Qt::Tool 会使程序无法结束，所以在关闭的时候重新设置一下
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    m_dialog->closeWindow();
    setLastKey();
    close();

    g_systemTimeControlWidget->deleteLater();
    g_systemTimeControlWidget = nullptr;
}

void SystemTimeControlWidget::closeEvent(QCloseEvent *event)
{
    if (showstatus) {
        event->ignore();
    } else {
        event->accept();
    }
}

