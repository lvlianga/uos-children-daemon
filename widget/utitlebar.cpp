#include "utitlebar.h"

// dtk
#include <DFontSizeManager>

#define ICONSIZE 72
#define CLOSESIZE 48
#define TITLESIZE 16

DCORE_USE_NAMESPACE

//字体颜色
const QColor labBlack_008 = QColor::fromRgbF(0, 0, 0, 0.08); //末尾小数
const QColor labBlack_085 = QColor::fromRgbF(0, 0, 0, 0.85);
const QColor labBlack_065 = QColor::fromRgbF(0, 0, 0, 0.65);
const QColor labBlack_050 = QColor::fromRgbF(0, 0, 0, 0.50);
const QColor labBlack_005 = QColor::fromRgbF(0, 0, 0, 0.20);

/**
 * @brief UTitlebar::UTitlebar 构造函数
 * @param parent
 * @author lvliang
 * @date 2021-11-10
 * @attention title的布局分四个部分
 */
UTitlebar::UTitlebar(QWidget *parent)
    : DWidget(parent)
    , m_closeButton(new DWindowCloseButton)
    , m_maintitleLabel(new QLabel(this))
    , m_blankLabel(new QLabel(this))
    , m_blankLabel1(new QLabel(this))
    , m_titleLabel(new QLabel(this))
    , m_iconlabel1(new QLabel(this))
    , m_iconlabel2(new QLabel(this))
    , m_iconlabel3(new QLabel(this))
    , m_iconlabel4(new QLabel(this))
    , m_mainLayout(new QVBoxLayout(this))
{
    QFont font1;
    QPalette palette;
    palette.setColor(QPalette::WindowText, labBlack_085);
    font1.setBold(true);
    font1.setWeight(QFont::DemiBold);
    font1.setPointSize(18);
    m_maintitleLabel->setFont(font1);
    m_maintitleLabel->setPalette(palette);

    QFont font2;
    QPalette palette1;
    palette1.setColor(QPalette::WindowText, labBlack_065);
    font2.setBold(true);
    font2.setWeight(QFont::ExtraLight);
    font2.setPointSize(11);
    m_titleLabel->setFont(font2);
    m_titleLabel->setPalette(palette1);

    m_blankLabel->hide();
    m_blankLabel->setFixedHeight(8);
    m_blankLabel->setContentsMargins(0, 0, 0, 0);

    m_blankLabel1->show();
    m_blankLabel1->setFixedHeight(40);
    m_blankLabel1->setContentsMargins(0, 0, 0, 0);

    // 初始化主布局
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    QHBoxLayout *titberLayout = new QHBoxLayout;
    titberLayout->setMargin(0);
    titberLayout->setSpacing(0);
    titberLayout->addStretch();
    titberLayout->addWidget(m_closeButton, 0, Qt::AlignRight | Qt::AlignTop);
    QWidget *titberwidget = new QWidget(this);
    titberwidget->setLayout(titberLayout);
    titberLayout->setContentsMargins(0, 0, 0, 0);
    titberwidget->setContentsMargins(0, 0, 0, 0);

    m_closeButton->setFixedHeight(48);
    m_closeButton->setIconSize(QSize(CLOSESIZE, CLOSESIZE));
    m_closeButton->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *iconHlayout = new QHBoxLayout(this);
    iconHlayout->addWidget(m_iconlabel1);
    iconHlayout->addWidget(m_iconlabel2);
    iconHlayout->addWidget(m_iconlabel3);
    iconHlayout->addWidget(m_iconlabel4);
    m_iconlabel1->hide();
    m_iconlabel2->hide();
    m_iconlabel3->hide();
    m_iconlabel4->hide();
    iconHlayout->setContentsMargins(0, 0, 0, 0);

    QWidget *iconwidget = new QWidget(this);
    iconwidget->setLayout(iconHlayout);

    iconwidget->setContentsMargins(0, 0, 0, 0);

    m_mainLayout->addWidget(titberwidget, 0, Qt::AlignTop | Qt::AlignRight);
    m_mainLayout->addWidget(m_blankLabel);
    m_mainLayout->addSpacing(8);
    m_mainLayout->addWidget(m_maintitleLabel, 0, Qt::AlignHCenter);
    m_mainLayout->addSpacing(7);
    m_mainLayout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    m_mainLayout->addSpacing(8);
    m_mainLayout->addWidget(m_blankLabel1, 0, Qt::AlignHCenter);
    m_mainLayout->addWidget(iconwidget, 0, Qt::AlignHCenter);
    m_mainLayout->addStretch();
    titberwidget->setContentsMargins(0, 0, 0, 0);
    m_maintitleLabel->setContentsMargins(0, 0, 0, 0);
    m_titleLabel->setContentsMargins(0, 0, 0, 0);
    iconwidget->setContentsMargins(0, 0, 0, 0);

    setLayout(m_mainLayout);

    setContentsMargins(0, 0, 0, 0);
    initConnections();
}

/**
 * @brief UTitlebar::settitleText 设置提示文字
 * @param miantext 主要字体
 * @param text 下午小字体
 * @author lvliang
 * @date 2021-11-12
 */
void UTitlebar::settitleText(const QString &miantext, const QString &text)
{
    m_maintitleLabel->setText(miantext);
    m_titleLabel->setText(text);
}

/**
 * @brief UTitlebar::seticon1Show 显示第一个图标
 * @param pixmap
 * @author lvliang
 * @date 2021-11-12
 */
void UTitlebar::seticon1Show(const QPixmap &pixmap)
{
    m_iconlabel1->setPixmap(pixmap);
    m_iconlabel1->setScaledContents(true);
    m_iconlabel1->setFixedSize(40, 40);
    m_iconlabel1->show();
    m_blankLabel1->hide();
}

/**
 * @brief UTitlebar::seticon2Show 显示第二个图标
 * @param pixmap 需要上传的图片
 * @author lvliang
 * @date 2021-11-12
 */
void UTitlebar::seticon2Show(const QPixmap &pixmap)
{
    m_iconlabel2->setPixmap(pixmap);
    m_iconlabel2->setScaledContents(true);
    m_iconlabel2->setFixedSize(40, 40);
    m_iconlabel2->show();
    m_blankLabel1->hide();
}

/**
 * @brief UTitlebar::seticon3Show 显示第三个图标
 * @param pixmap 需要上传的图片
 * @author lvliang
 * @date 2021-11-12
 */
void UTitlebar::seticon3Show(const QPixmap &pixmap)
{
    m_iconlabel3->setPixmap(pixmap);
    m_iconlabel3->setScaledContents(true);
    m_iconlabel3->setFixedSize(40, 40);
    m_iconlabel3->show();
    m_blankLabel1->hide();
}

/**
 * @brief UTitlebar::seticon4Show 显示第四个图标
 * @param pixmap 需要上传的图片
 * @author lvliang
 * @date 2021-11-12
 */
void UTitlebar::seticon4Show(const QPixmap &pixmap)
{
    m_iconlabel4->setPixmap(pixmap);
    m_iconlabel4->setScaledContents(true);
    m_iconlabel4->setFixedSize(40, 40);
    m_iconlabel4->show();
    m_blankLabel1->hide();
}

/**
 * @brief UTitlebar::setblanklabel1Hide 设置空白Label隐藏
 * @author lvliang
 * @date 2021-11-12
 */
void UTitlebar::setblanklabel1Hide()
{
    m_blankLabel1->hide();
}

/**
 * @brief UTitlebar::setblanklabel1Hide 设置空白Label显示
 * @author lvliang
 * @date 2021-11-12
 */
void UTitlebar::setblanklabelShow()
{
    m_blankLabel->show();
}

/**
 * @brief UTitlebar::initConnections 初始化信号槽
 * @author lvliang
 * @date 2021-11-12
 */
void UTitlebar::initConnections()
{
    connect(m_closeButton, &DWindowCloseButton::clicked, this, &UTitlebar::close);
}
