/**
 * @file     ancientpoems.h
 * @brief    古诗词锁屏界面
 * @author   lvliang
 * @date     2022/01/26
 * @copyright   Copyright (c) 2050
 * @attention
 * QT版本：5.11.3 (GCC 8.3.0, 64 bit)
*/

#ifndef ANCIENTPOEMS_H
#define ANCIENTPOEMS_H

#include <DAbstractDialog>

#include "../service/lock_screen_control.h"

DWIDGET_USE_NAMESPACE

class AncientPoems : public DAbstractDialog
{
    Q_OBJECT
public:
    /**
     * @brief AncientPoems
     * @author lvliang
     * @date 2022/01/26
     */
    AncientPoems();
    /**
     * @brief initUi              初始化UI
     * @author lvliang
     * @date 2022/01/26
     **/
    void initUi();
protected:
    void closeEvent(QCloseEvent *event);

public slots:
    /**
     * @brief slot_ApplyForUnlockDesktop 申请解锁
     * @author lvliang
     * @date 2022/01/26
     */
    void slot_ApplyForUnlockDesktop();
signals:
    /**
     * @brief signal_ApplyForUnlockDesktop 发送申请解锁的信号
     * @param id
     * @author lvliang
     * @date 2022/01/26
     */
    void signal_ApplyForUnlockDesktop(QString id);
};

#endif // ANCIENTPOEMS_H
