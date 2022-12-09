/**
 * @file     unlockbutton.h
 * @brief    锁屏按钮重构类
 * @author   lvliang
 * @date     2021-03-13
 * @copyright   Copyright (c) 2050
 * @attention
 * QT版本：5.11.3 (GCC 8.3.0, 64 bit)
*/

#ifndef UNLOCKBUTTON_H
#define UNLOCKBUTTON_H

#include <QPushButton>

class UnLockButton : public QPushButton
{
    Q_OBJECT
public:
    /**
     * @brief UnLockButton 锁屏按钮重绘
     * @author lvliang
     * @date 2020-03-13
     */
    UnLockButton(QString pixmap, QString text, int width, QWidget *parent = nullptr);

signals:
    /**
     * @brief signals_enter 点击解锁按钮
     * @author lvliang
     * @date 2020-03-13
     */
    void signals_enter();

protected:
    /**
     * @brief paintEvent 绘制锁屏按钮界面
     * @param event
     * @author lvliang
     * @date 2022-04-13
     */
    void paintEvent(QPaintEvent *event) override;
    /**
     * @brief mouseReleaseEvent 释放锁屏按钮
     * @param ev
     * @author lvliang
     * @date 2022-04-13
     */
    void mouseReleaseEvent(QMouseEvent *ev);  //抬起
    /**
     * @brief mouseReleaseEvent 释放锁屏按钮
     * @param ev
     * @author lvliang
     * @date 2022-04-13
     */
    void mousePressEvent(QMouseEvent *ev);  //点击

private:
    int isHorvered;// 0: normal 1:horver 2: enter

    QString m_pixmap;
    QString m_text;
    int m_width;
};

#endif // UNLOCKBUTTON_H
