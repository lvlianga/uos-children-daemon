#include "ubase_dialog.h"
#include "utitlebar.h"
#include "../service/httpclient.h"

#define FIXEDWIDTH 376
#define FIXEDHEIGHT 516
#define BOTTOMHEIGHT 32

UBaseDialog::UBaseDialog(QWidget *parent)
    : DAbstractDialog(parent)
    , m_titleBar(new UTitlebar)
    , m_stackWidget(new QStackedWidget(this))
    , findParentButton(new DSuggestButton)
{
    installEventFilter(this);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    initUI();
    initConnections();
}

/*******************************************************************************
 1. @函数:    setTitle
 2. @作者:    ut003015 吕亮
 3. @日期:    2021-11-12
 4. @说明:    初始化titilebar
*******************************************************************************/
void UBaseDialog::setTitle(const QString &text)
{

}

/*******************************************************************************
 1. @函数:    stackWidget
 2. @作者:    ut003015 吕亮
 3. @日期:    2021-11-12
 4. @说明:    获取堆栈窗口
*******************************************************************************/
QStackedWidget *UBaseDialog::stackWidget() const
{
    return m_stackWidget;
}

/*******************************************************************************
 1. @函数:    initConnections
 2. @作者:    ut003015 吕亮
 3. @日期:    2021-11-12
 4. @说明:    绑定信号槽
*******************************************************************************/
void UBaseDialog::initConnections()
{
    connect(m_titleBar, &UTitlebar::close, this, &UBaseDialog::onClose);
}

bool UBaseDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape) {
            onClose();
        }
    }
    return QDialog::eventFilter(obj, event);
}

/*******************************************************************************
 1. @函数:    onClose
 2. @作者:    ut003015 吕亮
 3. @日期:    2021-11-12
 4. @说明:    关闭弹窗，告诉应用弹窗关闭
*******************************************************************************/
void UBaseDialog::onClose()
{

}

/*******************************************************************************
 1. @函数:    initUI
 2. @作者:    ut003015 吕亮
 3. @日期:    2021-11-12
 4. @说明:    初始化UI界面
*******************************************************************************/
void UBaseDialog::initUI()
{
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setSpacing(0);
    vlayout->setMargin(0);
    vlayout->addWidget(m_titleBar, 0, Qt::AlignTop);
    vlayout->addWidget(m_stackWidget);
    vlayout->addWidget(findParentButton, 0, Qt::AlignHCenter);
    vlayout->setContentsMargins(0, 0, 0, BOTTOMHEIGHT);

    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(vlayout);
    mainWidget->setContentsMargins(0, 0, 0, 0);

    // 设置布局
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(mainWidget);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    m_stackWidget->setContentsMargins(0, 0, 0, 0);

    setLayout(m_mainLayout);
    setContentsMargins(0, 0, 0, 0);

    setFixedSize(FIXEDWIDTH, FIXEDHEIGHT);
}
