/**
 * @file     maskwidget.h
 * @brief    多屏显示灰化界面
 * @author   lvliang
 * @date     2021-03-13
 * @copyright   Copyright (c) 2050
 * @attention
 * QT版本：5.11.3 (GCC 8.3.0, 64 bit)
*/

#ifndef MASKWIDGET_H
#define MASKWIDGET_H
#include <QWidget>
class QGraphicsBlurEffect;
class MaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MaskWidget(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    //设置灰化程度
    QGraphicsBlurEffect *m_graphicEffect;
};
#endif // MASKWIDGET_H
