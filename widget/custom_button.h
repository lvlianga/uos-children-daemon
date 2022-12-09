/*
 * Author:     liumaochuan <liumaochuan@uniontech.com>
 *
 * Maintainer: liumaochuan <liumaochuan@uniontech.com>
 */

#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include <QMouseEvent>
//#include <QPushButton>
#include <QLabel>

class custombutton : public QLabel
{
    Q_OBJECT
public:
    custombutton();
    custombutton(const QString &normalPath, const QString &leavePath, const QString &enterEvent, const int &size);

protected:
    void mouseReleaseEvent(QMouseEvent *ev);  //抬起
    void mousePressEvent(QMouseEvent *ev);  //点击
    void enterEvent(QEvent *e) override;//鼠标进入事件
    void leaveEvent(QEvent *e) override;//鼠标离开事件

private:
    /**
     * @brief setIcon 设置按钮图标
     * @param path 图片的路径
     * @author liumaochuan
     * @date 2022-03-13
     */
    void setIcon(const QString &path);

signals:
    /**
     * @brief signal_pressed 按下
     * @author liumaochuan
     * @date 2022-03-13
     */
    void signal_pressed();
    /**
     * @brief signal_release 抬起
     * @author liumaochuan
     * @date 2022-03-13
     */
    void signal_release();

private:
    //悬浮图片路径
    QString m_LeavePath;
    //点击图片路径
    QString m_EnterPath;
    //正常图片路径
    QString m_normalPath;
    //图片大小
    int m_size;
};

#endif // CUSTOMBUTTON_H
