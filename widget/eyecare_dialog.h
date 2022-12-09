/**
 * @file     eyecaredialog.h
 * @brief    护眼健康提示框
 * @author   lidudongyu
 * @date     2021-03-13
 * @copyright   Copyright (c) 2050
 * @attention
 * QT版本：5.11.3 (GCC 8.3.0, 64 bit)
*/

#ifndef EYECAREDIALOG_H
#define EYECAREDIALOG_H

#include <QTimer>

#include <DAbstractDialog>
#include <DLabel>

DWIDGET_USE_NAMESPACE

class EyeCareDialog : public DAbstractDialog
{
    Q_OBJECT
public:
    explicit EyeCareDialog(QWidget *parent = nullptr);
    ~EyeCareDialog() override;

    void showDialog();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    /**
     * @brief initUi 初始化UI
     */
    void initUi();

signals:
    /**
     * @brief signal_close 关闭护眼健康提示框信号
     */
    void signal_close();

private:
    //计时器关闭当前护眼健康提示框
    QTimer m_timer;
    //护眼健康提示
    DLabel *m_textLabel = nullptr;
};

#endif // EYECAREDIALOG_H
