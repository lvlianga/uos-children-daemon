#include "mask_widget.h"

#include <QGraphicsBlurEffect>
#include <QKeyEvent>

#include "../service/lock_screen_control.h"

MaskWidget::MaskWidget(QWidget *parent)
    : QWidget(parent)
    , m_graphicEffect(new QGraphicsBlurEffect)
{
    m_graphicEffect->setBlurRadius(30);
    m_graphicEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);
    setGraphicsEffect(m_graphicEffect);

    setWindowOpacity(0.7); // 设置透明度
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool); // 屏蔽按钮  置顶  dock栏不显示应用图标(会使程序无法结束)
}

void MaskWidget::keyPressEvent(QKeyEvent *event)
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

void MaskWidget::closeEvent(QCloseEvent *event)
{
    if (event->spontaneous()) {
        event->ignore();
    } else {
        event->accept();
    }
}
