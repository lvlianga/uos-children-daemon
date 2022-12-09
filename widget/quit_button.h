#ifndef QUITBUTTON_H
#define QUITBUTTON_H

#include <QPushButton>
#include <DWidget>

class QuitButton: public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief quitButton 锁屏按钮重绘
     * @author lvliang
     * @date 2022-06-14
     */
    QuitButton(QWidget *parent = nullptr);

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
};

#endif // QUITBUTTON_H
