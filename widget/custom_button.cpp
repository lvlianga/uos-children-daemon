/*
 * Author:     liumaochuan <liumaochuan@uniontech.com>
 *
 * Maintainer: liumaochuan <liumaochuan@uniontech.com>
 */

#include "custom_button.h"
#include <QIcon>

custombutton::custombutton()
{

}

custombutton::custombutton(const QString &normalPath, const QString &leavePath, const QString &enterEvent, const int &size)
{
    m_LeavePath = normalPath;
    m_EnterPath = leavePath;
    m_normalPath = leavePath;
    m_size = size;
    setIcon(m_LeavePath);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void custombutton::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    setIcon(m_normalPath);
    emit signal_release();
}

void custombutton::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    setIcon(m_LeavePath);
    emit signal_pressed();
}

void custombutton::enterEvent(QEvent *e)
{
    Q_UNUSED(e);
    setIcon(m_EnterPath);
}

void custombutton::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);
    setIcon(m_LeavePath);
}

void custombutton::setIcon(const QString &path)
{
    // 适应当前设备分辨率
    const qreal ratio = devicePixelRatioF();

    QPixmap pixmap = QIcon::fromTheme(path).pixmap(60, 60);
    pixmap.scaled(size() * ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(pixmap);
}
