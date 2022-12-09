#include "curtain_widget.h"

#include <QGraphicsBlurEffect>
#include <QKeyEvent>
#include <QPalette>
#include <QButtonGroup>
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>


#include "../control/signal_interface.h"
#include "../service/lock_screen_control.h"
#include "../control/config_worker.h"
#include "public_method.h"
#include "eyeexercises_widget.h"
#include "unlock_button.h"
#include "quit_button.h"
#include "custom_button.h"

#define RANDOM 6
#define NEXTONE 30000

const int buttonW = 60;
const QString LeftNormal = ":/images/light/left_normal_24px.svg";
const QString LeftHover = ":/images/light/left_hover_24px.svg";
const QString LeftPress = ":/images/light/left_press_24px.svg";
const QString RightNormal = ":/images/light/right_normal_24px.svg";
const QString RightHover = ":/images/light/right_hover_24px.svg";
const QString RightPress = ":/images/light/right_press_24px.svg";
const QString unlcokpicture = ":/images/light/unlock.svg";
const QString lcokpicture = ":/images/light/lock.svg";
const int NormalCount = 5;

/**
 * @brief CurtainWidget::CurtainWidget 桌面锁屏界面
 * @param rect
 * @param parent
 * @author lvliang
 * @attention
 */
CurtainWidget::CurtainWidget(QRect rect, QWidget *parent)
    : QWidget(parent)
    , m_graphicEffect(new QGraphicsBlurEffect)
    , m_timer(new QTimer)
    , m_mainWidget(new QWidget)
    , m_quitIcon(new QuitButton)
    , m_topWidget(new QWidget)
    , m_centerWidget(new QWidget)
    , m_exeiseButton(new UnLockButton(":/images/light/smilenormal.svg", tr("做眼保健操"), 194))
    , m_unLockButton(new UnLockButton(":/images/light/unlocknormal.svg", tr("我要解锁"), 176))
    , m_quitLayout(new QHBoxLayout)
    , m_topLayout(new QVBoxLayout)
    , m_midLayout(new QHBoxLayout)
    , m_hButtonLayout(new QHBoxLayout)
    , m_mainLayout(new QVBoxLayout)
    , m_pLeftButton(new custombutton(LeftNormal, LeftHover, LeftPress, buttonW))
    , m_pRightButton(new custombutton(RightNormal, RightHover, RightPress, buttonW))
    , m_timelab(new QLabel)
    , m_datelab(new QLabel)
    , m_username(PublicMethod::getCurrentUsername())
{
    currentWidth = rect.width();
    currentHeight = rect.height();

    QDateTime currenttime = QDateTime::currentDateTime();
    m_timelab->setText(currenttime.toString("hh:mm"));
    m_datelab->setText(currenttime.toString("MM%1").arg(tr("月")) + currenttime.toString("dd%1 ddd").arg(tr("日")).replace(tr("周"), tr("星期")));

    // 添加ImageOpacity属性;
    this->setProperty("ImageOpacity", 1.0);
    // 动画切换类;
    m_opacityAnimation = new QPropertyAnimation(this, "ImageOpacity");
    // 这里要设置的动画时间小于图片切换时间;
    m_opacityAnimation->setDuration(1000);
    // 设置ImageOpacity属性值的变化范围;
    m_opacityAnimation->setStartValue(1.0);
    m_opacityAnimation->setEndValue(0.0);

    randomData();

    m_preDrawImageIndex = m_imageList.count() - 1;
    m_nextDrawImageIndex = 1;

    //设置当前首次显示的图片
    setCurrentIndex(m_currentDrawImageIndex);
    m_theNextPixmap = m_currentPixmap;
    m_theCurrentPixmap = m_currentPixmap;
    m_timer->start(1000);

    initUI();
    initConnect();

    setWindowOpacity(1); // 设置透明度
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool); // 屏蔽按钮  置顶  dock栏不显示应用图标(会使程序无法结束)
}

CurtainWidget::~CurtainWidget()
{
    delete m_eyeExerciseWidget;
    m_eyeExerciseWidget = nullptr;
}

/**
 * @brief CurtainWidget::initUI 初始化界面
 * @author lvliang
 * @attention
 */
void CurtainWidget::initUI()
{
    m_quitIcon->hide();
    m_unLockButton->show();

    QFont font;
    font.setPixelSize(60);
    font.setWeight(QFont::DemiBold);
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    m_timelab->setPalette(pe);
    m_timelab->setFont(font);

    QFont font1;
    font1.setPixelSize(20);
    m_datelab->setPalette(pe);
    m_datelab->setFont(font1);

    m_quitLayout->addStretch();
    m_quitLayout->addWidget(m_quitIcon);
    m_quitLayout->setMargin(0);
    m_quitLayout->setContentsMargins(0, 0, 32, 0);

    m_topLayout->setContentsMargins(0, 0, 0, 0);
    m_datelab->setContentsMargins(0, 0, 0, 0);
    m_timelab->setContentsMargins(0, 0, 0, 0);

    m_topLayout->addWidget(m_timelab, 0, Qt::AlignCenter);
    m_topLayout->addWidget(m_datelab, 0, Qt::AlignCenter);

    m_topWidget->setLayout(m_topLayout);
    m_topWidget->setFixedSize(200, 90);

    //左切换按钮
    m_pLeftButton->setFixedWidth(buttonW);
    m_pLeftButton->setContentsMargins(0, 0, 0, 0);
    m_pLeftButton->setFocusPolicy(Qt::NoFocus);
    m_pLeftButton->installEventFilter(this);

    //右切换按钮
    m_pRightButton->setFixedWidth(buttonW);
    m_pRightButton->setContentsMargins(0, 0, 0, 0);
    m_pRightButton->setFocusPolicy(Qt::NoFocus);
    m_pRightButton->installEventFilter(this);

    //左右按钮布局
    m_midLayout->addWidget(m_pLeftButton);
    m_midLayout->addStretch();
    m_midLayout->addWidget(m_pRightButton);
    m_midLayout->setContentsMargins(32, 268, 32, 111);

    //眼保健操解锁按钮布局
    QHBoxLayout *pushHlayout = new QHBoxLayout;
    pushHlayout->addStretch();
    pushHlayout->addWidget(m_exeiseButton);
    pushHlayout->addSpacing(8);
    pushHlayout->addWidget(m_unLockButton);
    pushHlayout->setContentsMargins(0, 0, 32, 120);

    //主布局
    m_mainLayout->addSpacing(56);
    m_mainLayout->setMargin(0);
    m_mainLayout->addLayout(m_quitLayout);
    m_mainLayout->addWidget(m_topWidget, 0, Qt::AlignCenter);
    m_mainLayout->addLayout(m_midLayout);
    m_mainLayout->addStretch();
    m_mainLayout->addLayout(pushHlayout, Qt::AlignBottom | Qt::AlignRight);

    setLayout(m_mainLayout);
}

/**
 * @brief CurtainWidget::initConnect 初始化信号槽
 * @author lvliang
 */
void CurtainWidget::initConnect()
{
    connect(m_timer, &QTimer::timeout, this, &CurtainWidget::updateTime);
    connect(m_quitIcon, &QuitButton::signals_enter, this, &CurtainWidget::quitDesktop);
    connect(m_exeiseButton, &UnLockButton::signals_enter, this, &CurtainWidget::openEyeExercise);
    connect(m_unLockButton, &UnLockButton::signals_enter, this, &CurtainWidget::unLockDesktop);
    // 设置图片切换时钟槽函数;
    connect(&m_imageChangeTimer, SIGNAL(timeout()), this, SLOT(onImageChangeTimeout()));
    // 透明度变化及时更新绘图;
    connect(m_opacityAnimation, SIGNAL(valueChanged(const QVariant &)), this, SLOT(update()));
    connect(m_pLeftButton, SIGNAL(signal_release()), this, SLOT(onImageLeftButtonClicked()));
    connect(m_pRightButton, SIGNAL(signal_release()), this, SLOT(onImageRightButtonClicked()));
    connect(SignalInterface::intance(), &SignalInterface::signal_pushButton,  this, &CurtainWidget::setUnLockPushButton);
}

/**
 * @brief CurtainWidget::updateTime 更新时间
 * @author lvliang
 */
void CurtainWidget::updateTime()
{
    QDateTime currenttime = QDateTime::currentDateTime();
    m_timelab->setText(currenttime.toString("hh:mm"));
    m_datelab->setText(currenttime.toString("MM%1").arg(tr("月")) + currenttime.toString("dd%1 ddd").arg(tr("日")).replace(tr("周"), tr("星期")));
}

/**
 * @brief CurtainWidget::unLockDesktop 打开解锁二维码
 * @author lvliang
 */
void CurtainWidget::unLockDesktop()
{
    m_unLockButton->setEnabled(false);
    emit signal_sendUnlock(ConfigWorker::instance()->getConfigValue(m_username, "DisableModeId"));
}

void CurtainWidget::quitDesktop()
{
    m_unLockButton->setEnabled(false);
    emit signal_sendQuitDesktop(ConfigWorker::instance()->getConfigValue(m_username, "DisableModeId"));
}

/**
 * @brief CurtainWidget::randomData 设置背景图片写入
 * @author lvliang
 */
void CurtainWidget::randomData()
{
    //清空容器
    clearList();

    for (int i = 0; i < NormalCount; i++) {
        switch (i) {
        case 0:
            addImage(drawImage(QString(BGPATH) + "/BG1.png"));
            break;
        case 1:
            addImage(drawImage(QString(BGPATH) + "/BG2.png"));
            break;
        case 2:
            addImage(drawImage(QString(BGPATH) + "/BG3.png"));
            break;
        case 3:
            addImage(drawImage(QString(BGPATH) + "/BG4.png"));
            break;
        case 4:
            addImage(drawImage(QString(BGPATH) + "/BG5.png"));
            break;
        }
    }
}

/**
 * @brief CurtainWidget::drawImage 返回图片
 * @param path 需要给的图片路径
 * @author lvliang
 * @return 返回一个QImage的图片
 */
QImage CurtainWidget::drawImage(QString path)
{
    QImage image(path);
    return image;
}

/**
 * @brief CurtainWidget::addImage 添加图片到容器中
 * @param imageFileName QImage的图片
 * @author lvliang
 */
void CurtainWidget::addImage(QImage imageFileName)
{
    m_imageList.append(imageFileName);
}

/**
 * @brief CurtainWidget::clearList 清空容器
 * @author lvliang
 */
void CurtainWidget::clearList()
{
    m_imageList.clear();
}

/**
 * @brief CurtainWidget::setCurrentIndex 设置当前显示的图片
 * @param index 图片的标号
 * @author lvliang
 */
void CurtainWidget::setCurrentIndex(int index)
{
    // 数据校验
    if (index > m_imageList.count() - 1) {
        m_currentDrawImageIndex = 0;
    }

    if (index < 0) {
        m_currentDrawImageIndex = m_imageList.count() - 1;
    }

    m_currentPixmap = QPixmap::fromImage(m_imageList.at(m_currentDrawImageIndex));

    update();
}

/**
 * @brief CurtainWidget::setPreIndex 设置上一张图片
 * @param index 图片的标号
 * @author lvliang
 */
void CurtainWidget::setPreIndex(int index)
{
    // 数据校验
    if (index > m_imageList.count() - 1) {
        m_preDrawImageIndex = 0;
    }

    if (index < 0) {
        m_preDrawImageIndex = m_imageList.count() - 1;
    }

    m_prePixmap = QPixmap::fromImage(m_imageList.at(m_preDrawImageIndex));

    m_opacityAnimation->stop();
    m_opacityAnimation->start();

    update();
}

/**
 * @brief CurtainWidget::setNextIndex 设置下一张图片
 * @param index 图片的标号
 * @author lvliang
 */
void CurtainWidget::setNextIndex(int index)
{
    // 数据校验
    if (index > m_imageList.count() - 1) {
        m_nextDrawImageIndex = 0;
    }

    if (index < 0) {
        m_nextDrawImageIndex = m_imageList.count() - 1;
    }

    m_nextPixmap = QPixmap::fromImage(m_imageList.at(m_nextDrawImageIndex));

    m_opacityAnimation->stop();
    m_opacityAnimation->start();

    update();
}

/**
 * @brief CurtainWidget::onImageLeftButtonClicked 点击左边切换按钮
 * @author lvliang
 */
void CurtainWidget::onImageLeftButtonClicked()
{
    m_preDrawImageIndex--;
    m_currentDrawImageIndex--;
    m_nextDrawImageIndex--;
    setPreIndex(m_preDrawImageIndex);
    setCurrentIndex(m_currentDrawImageIndex);
    setNextIndex(m_nextDrawImageIndex);
    m_theNextPixmap = m_currentPixmap;
    m_theCurrentPixmap = m_nextPixmap;
    m_imageChangeTimer.start(NEXTONE);
}

/**
 * @brief CurtainWidget::onImageRightButtonClicked 点击右边切换按钮
 * @author lvliang
 */
void CurtainWidget::onImageRightButtonClicked()
{
    ++m_preDrawImageIndex;
    ++m_currentDrawImageIndex;
    ++m_nextDrawImageIndex;
    setPreIndex(m_preDrawImageIndex);
    setCurrentIndex(m_currentDrawImageIndex);
    setNextIndex(m_nextDrawImageIndex);
    m_theNextPixmap = m_currentPixmap;
    m_theCurrentPixmap = m_prePixmap;
    m_imageChangeTimer.start(NEXTONE);
}

void CurtainWidget::onImageChangeTimeout()
{
    ++m_preDrawImageIndex;
    ++m_currentDrawImageIndex;
    ++m_nextDrawImageIndex;
    setPreIndex(m_preDrawImageIndex);
    setCurrentIndex(m_currentDrawImageIndex);
    setNextIndex(m_nextDrawImageIndex);
    m_theNextPixmap = m_currentPixmap;
    m_theCurrentPixmap = m_prePixmap;
    setCurrentIndex(m_currentDrawImageIndex);
}

void CurtainWidget::slotPlayTimeChange(qint64 position)
{
    qint64 time = m_eyeExerciseWidget->getVideoDurationTime() - position;
    if (time == 0 && position != 0) {
        closeEyeCare();
    }
}

void CurtainWidget::slotStateChanged(QMediaPlayer::State newState)
{
    if (newState == QMediaPlayer::StoppedState) {
        closeEyeCare();
    }
}

void CurtainWidget::startPlay()
{
    // 添加完图片之后，根据图片多少设置图片切换按钮;
//    initChangeImageButton();
    qInfo() << "m_currentDrawImageIndex == " << m_currentDrawImageIndex;
    setCurrentIndex(m_currentDrawImageIndex);
    if (m_imageList.count() != 1) {
        qInfo() << "m_imageChangeTimer start";
        m_imageChangeTimer.start(NEXTONE);
    }
}

void CurtainWidget::setUIType(int type)
{
    if (0 == type) {
        m_quitIcon->show();
        m_unLockButton->hide();
    } else {
        m_quitIcon->hide();
        m_unLockButton->show();
    }
}

void CurtainWidget::openEyeExercise()
{
    emit signalOpenEyeCare();
    QScreen *mainScreen = qApp->primaryScreen();
    m_eyeExerciseWidget = new EyeExercisesWidget;
    m_eyeExerciseWidget->setGeometry(mainScreen->geometry());
    m_eyeExerciseWidget->show();
    m_eyeExerciseWidget->showFullScreen();
    connect(m_eyeExerciseWidget, &EyeExercisesWidget::signalCloseEyeCare, this, &CurtainWidget::closeEyeCare);
    connect(m_eyeExerciseWidget, &EyeExercisesWidget::signal_playTimeChange, this, &CurtainWidget::slotPlayTimeChange);
    connect(m_eyeExerciseWidget, &EyeExercisesWidget::signal_stateChanged, this, &CurtainWidget::slotStateChanged);
}

void CurtainWidget::closeEyeCare()
{
    m_eyeExerciseWidget->close();
    m_eyeExerciseWidget->deleteLater();
}

/**
 * @brief CurtainWidget::setUnLockPushButton 解锁图标按钮可用
 * @author lvliang
 */
void CurtainWidget::setUnLockPushButton()
{
    m_unLockButton->setEnabled(true);
}

/**
 * @brief CurtainWidget::paintEvent 桌面锁屏壁纸
 * @param event
 * @author lvliang
 */
void CurtainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QRect imageRect = this->rect();
    //适应当前设备分辨率
    const auto ratio = devicePixelRatioF();

    //如果图片为空则表示为默认图片
    if (m_imageList.isEmpty()) {
        QPixmap backPixmap = QPixmap(":/images/light/BG1.png");
        if (!backPixmap.isNull()) {
            painter.drawPixmap(imageRect, backPixmap.scaled(imageRect.size() * ratio, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        }
    } else {
        //图片切换渐变显示
        float imageOpacity = this->property("ImageOpacity").toFloat();
        painter.setOpacity(1);
        painter.drawPixmap(imageRect, m_theNextPixmap.scaled(imageRect.size() * ratio, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        painter.setOpacity(imageOpacity);
        painter.drawPixmap(imageRect, m_theCurrentPixmap.scaled(imageRect.size() * ratio, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    painter.restore();
    return QWidget::paintEvent(event);
}

void CurtainWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        break;
    case Qt::Key_Shift:
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void CurtainWidget::showEvent(QShowEvent *event)
{
    startPlay();
    return QWidget::showEvent(event);
}

void CurtainWidget::closeEvent(QCloseEvent *event)
{
    if (event->spontaneous()) {
        event->ignore();
    } else {
        event->accept();
    }
}
