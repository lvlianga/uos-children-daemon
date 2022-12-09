/**
 * @file     utitlebar.h
 * @brief    二维码绘制控件
 * @author   lvliang
 * @date     2021-03-13
 * @copyright   Copyright (c) 2050
 * @attention
 * QT版本：5.11.3 (GCC 8.3.0, 64 bit)
*/
#ifndef UTITLEBAR_H
#define UTITLEBAR_H

// dtk
#include <DWidget>
#include <DWindowCloseButton>
#include <DIconButton>
#include <DLabel>

// qt
#include <QHBoxLayout>
#include <QVBoxLayout>

DWIDGET_USE_NAMESPACE

class UTitlebar : public DWidget
{
    Q_OBJECT
public:
    /**
     * @brief UTitlebar 构造函数
     * @param parent
     * @author lvliang
     * @date 2021-11-10
     * @attention title的布局分四个部分
     */
    UTitlebar(QWidget *parent = nullptr);
    // 设置标题文字
    /**
     * @brief settitleText 设置提示文字
     * @param miantext 主要字体
     * @param text 下午小字体
     * @author lvliang
     * @date 2021-11-12
     */
    void settitleText(const QString &miantext, const QString &text);
    /**
     * @brief seticon1Show 显示第一个图标
     * @param pixmap
     * @author lvliang
     * @date 2021-11-12
     */
    void seticon1Show(const QPixmap &pixmap);
    /**
     * @brief UTitlebar::seticon2Show 显示第二个图标
     * @param pixmap
     * @author lvliang
     * @date 2021-11-12
     */
    void seticon2Show(const QPixmap &pixmap);
    /**
     * @brief UTitlebar::seticon3Show 显示第三个图标
     * @param pixmap
     * @author lvliang
     * @date 2021-11-12
     */
    void seticon3Show(const QPixmap &pixmap);
    /**
     * @brief UTitlebar::seticon4Show 显示第四个图标
     * @param pixmap
     * @author lvliang
     * @date 2021-11-12
     */
    void seticon4Show(const QPixmap &pixmap);
    /**
     * @brief setblanklabel1Hide 设置空白Label显示
     * @author lvliang
     * @date 2021-11-12
     */
    void setblanklabelShow();
    /**
     * @brief setblanklabel1Hide 设置空白Label隐藏
     * @author lvliang
     * @date 2021-11-12
     */
    void setblanklabel1Hide();

signals:
    // 关闭按钮被点击
    void close();

private:
    /**
     * @brief initConnections 初始化信号槽
     * @author lvliang
     * @date 2021-11-12
     */
    void initConnections();
    // 关闭按钮
    DWindowCloseButton *m_closeButton = nullptr;
    QLabel *m_maintitleLabel;//主标题
    QLabel *m_blankLabel;//空白图片
    QLabel *m_blankLabel1;//空白图片
    QLabel *m_titleLabel;//副标题
    QLabel *m_iconlabel1;//显示图标1
    QLabel *m_iconlabel2;//显示图标2
    QLabel *m_iconlabel3;//显示图标3
    QLabel *m_iconlabel4;//显示图标4
    // 布局
    QVBoxLayout *m_mainLayout = nullptr;

};

#endif // UTITLEBAR_H
