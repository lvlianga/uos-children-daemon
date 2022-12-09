/**
 * @file     ubasedialog.h
 * @brief    设置二维码界面
 * @author   lvliang
 * @date     2021-11-12
 * @copyright   Copyright (c) 2050
 * @attention
 * QT版本：5.11.3 (GCC 8.3.0, 64 bit)
*/
#ifndef UBASEDIALOG_H
#define UBASEDIALOG_H

// dtk
#include <DAbstractDialog>
#include <DTitlebar>
#include <DSuggestButton>

// qt
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QKeyEvent>

DWIDGET_USE_NAMESPACE

class UTitlebar;
class UBottomWidget;
class UBaseDialog : public DAbstractDialog
{
    Q_OBJECT
public:
    UBaseDialog(QWidget *parent = nullptr);

    /**
     * @brief setTitle 设置标题文字和图表
     * @param text
     * @author lvliang
     * @date 2021-11-12
     */
    void setTitle(const QString &text);
    /**
     * @brief stackWidget
     * @return 返回切换的布局
     */
    QStackedWidget *stackWidget() const;

signals:
    void switchType();

public slots:
    // 关闭当前弹窗，通知调起应用
    void onClose();

private:
    /**
     * @brief initUI 初始化UI
     * @author lvliang
     * @date 2021-11-12
     */
    void initUI();
    /**
     * @brief initConnections 初始化信号槽
     * @author lvliang
     * @date 2021-11-12
     */
    void initConnections();
    /**
     * @brief eventFilter 添加监听事件 点击Esc按钮关闭该界面
     * @param obj
     * @param event
     * @author lvliang
     * @date 2021-11-12
     */
    bool eventFilter(QObject *obj, QEvent *event) override;
    // 标题栏
    UTitlebar *m_titleBar = nullptr;
    // 可供切换的布局
    QStackedWidget *m_stackWidget = nullptr;
    // 底部按钮
    DSuggestButton *findParentButton = nullptr;
    // 垂直布局
    QVBoxLayout *m_mainLayout = nullptr;
};

#endif // UBASEDIALOG_H
