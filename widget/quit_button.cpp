#include "quit_button.h"

#include <QPen>
#include <QPainter>
#include <QLabel>


QuitButton::QuitButton(QWidget *parent)
    : QPushButton(parent)
{
    //初始值设置为不点击
    isHorvered = false;
    setFixedSize(144, 64);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::FramelessWindowHint);
    //设置背景为透明
    setAttribute(Qt::WA_TranslucentBackground);
    setContentsMargins(0, 0, 0, 0);
}

void QuitButton::paintEvent(QPaintEvent *event)
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

    QRect rectText;//画文字区域
    QFont font("NotoSansCJKSC");
    font.setPixelSize(30);
    rectText.setX(rect.x() + 42);
    rectText.setY(rect.y() + 9);
    rectText.setWidth(60);
    rectText.setHeight(45);

    QPen pen1;
    pen1.setColor(Qt::white);
    painter.setPen(pen1);
    painter.setFont(font);

    painter.drawText(rectText, tr("退出"));

    painter.restore();
}

void QuitButton::mouseReleaseEvent(QMouseEvent *ev)
{
    isHorvered = 0;
    update();
    signals_enter();
}

void QuitButton::mousePressEvent(QMouseEvent *ev)
{
    isHorvered = 1;
    update();
}
