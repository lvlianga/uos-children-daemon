#include "eyecare_dialog.h"

#include <DWidget>
#include <DWindowCloseButton>

#include <QLayout>
#include <QDBusInterface>

#define TIME (5 * 60 * 1000)

EyeCareDialog::EyeCareDialog(QWidget *parent)
    : DAbstractDialog(parent)
{
    setFixedSize(460, 360);
    initUi();

    m_timer.setInterval(TIME);
    connect(&m_timer, &QTimer::timeout, this, [this]() {
        close();
    });
}

EyeCareDialog::~EyeCareDialog()
{

}

void EyeCareDialog::showDialog()
{
    if (m_timer.isActive()) {
        m_timer.stop();
    }

    // TODO show之前 m_textLabel要根配置文件设置text
    QDBusInterface interface("com.deepin.daemon.ChildrenGuard.ConfigManager",
                                 "/com/deepin/daemon/ChildrenGuard/ConfigManager",
                                 "com.deepin.daemon.ChildrenGuard.ConfigManager",
                                 QDBusConnection::systemBus());
    QDBusMessage msg = interface.call(QDBus::Block, "Value", "EyeCareInterval");
    QString interval;
    if (msg.type() == QDBusMessage::ReplyMessage) {
        QVariant val = msg.arguments().first();
        interval = val.toString();
    }

    m_textLabel->setText(tr("您已使用电脑%1分钟，请注意保护眼睛").arg(interval));

    show();
    m_timer.start();
}

void EyeCareDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    deleteLater();
    emit signal_close();
}

void EyeCareDialog::initUi()
{
    QPalette paBack;
    paBack.setColor(QPalette::Background, Qt::white);

    QFrame *frame = new QFrame(this);
    frame->setFixedSize(460, 360);
    frame->setPalette(paBack);
    frame->setAutoFillBackground(true);

    // 关闭按钮
    DWindowCloseButton *closeBtn = new DWindowCloseButton(frame);
    closeBtn->setFocusPolicy(Qt::NoFocus);
    closeBtn->setIconSize(QSize(50, 50));
    connect(closeBtn, &DWindowCloseButton::clicked, this, [ this ]() {
        this->close();
    });

    DLabel *iconLabel = new DLabel(frame);
    iconLabel->setFixedSize(300, 190);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(QPixmap(":/images/light/eyecare.png"));

    QFont font("NotoSansCJKsc");
    font.setPixelSize(15);
    font.setWeight(QFont::DemiBold);

    m_textLabel = new DLabel(frame);
    m_textLabel->setMinimumSize(258, 22);
    m_textLabel->setFont(font);
    m_textLabel->setAlignment(Qt::AlignCenter);
    m_textLabel->setWordWrap(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(frame);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addWidget(closeBtn, 0, Qt::AlignRight);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(iconLabel, 0, Qt::AlignHCenter);
    mainLayout->addSpacing(30);
    mainLayout->addWidget(m_textLabel, 0, Qt::AlignHCenter);
    mainLayout->addStretch();
}
