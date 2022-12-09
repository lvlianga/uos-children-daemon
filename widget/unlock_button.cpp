#include "unlock_button.h"
#include <QString>
#include <QPainter>
#include <QDebug>

//const QString unlcoknormal = ":/images/light/unlocknormal.svg";

/**
 * @brief UnLockButton::UnLockButton 锁屏按钮重绘
 * @author lvliang
 * @date 2020-03-13
 */
UnLockButton::UnLockButton(QString pixmap, QString text, int width, QWidget *parent)
    : QPushButton(parent)
    , m_pixmap(pixmap)
    , m_text(text)
    , m_width(width)
{
    //初始值设置为不点击
    isHorvered = false;
    setFixedSize(m_width, 60);
    setWindowFlags(Qt::FramelessWindowHint);
    //设置背景为透明
    setAttribute(Qt::WA_TranslucentBackground);
    setContentsMargins(0, 0, 0, 0);
}

/**
 * @brief UnLockButton::paintEvent 画解锁按钮图标
 * @param event
 * @author lvliang
 * @date 2020-03-13
 */
void UnLockButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);//反锯齿

    QPen pen;
    pen.setColor(Qt::transparent);
    QColor btnBrushColor(Qt::black);

    if (isHorvered == 0) {
        btnBrushColor.setAlphaF(0.45);
    } else {
        btnBrushColor.setAlphaF(0.65);
    }

    QBrush btnBrush(btnBrushColor);
    painter.setPen(pen);
    painter.setBrush(btnBrush);
    QRect rect = this->rect();

    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);

    painter.drawRoundedRect(rect, rect.height() / 2, rect.height() / 2);

    // 适应当前设备分辨率
    const qreal ratio = devicePixelRatioF();

    QImage image(m_pixmap);
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap.scaled(size()*ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QRect rectmap;//画图标区域
    rectmap.setX(rect.x() + 16);
    rectmap.setY(rect.y() + 10);
    rectmap.setWidth(40);
    rectmap.setHeight(40);

    QRect rectText;//画文字区域
    QFont font;
    font.setPixelSize(22);
    rectText.setX(rect.x() + 16 + 40 + 8);
    rectText.setY(rect.y() + 11);
    rectText.setWidth(88);
    if (194 == m_width) {
        rectText.setWidth(110);
    }

    rectText.setHeight(33);

    QPen pen1;
    pen1.setColor(Qt::white);
    painter.setPen(pen1);
    painter.setFont(font);

    painter.drawPixmap(rectmap, pixmap);
    painter.drawText(rectText, m_text);

    painter.restore();
}

/**
 * @brief UnLockButton::mouseReleaseEvent 释放锁屏按钮
 * @param ev
 * @author lvliang
 * @date 2020-03-13
 */
void UnLockButton::mouseReleaseEvent(QMouseEvent *ev)
{
    isHorvered = 0;
    update();
    signals_enter();
}

/**
 * @brief UnLockButton::mousePressEvent 点击锁屏按钮
 * @param ev
 * @author lvliang
 * @date 2020-03-13
 */
void UnLockButton::mousePressEvent(QMouseEvent *ev)
{
    isHorvered = 1;
    update();
}


