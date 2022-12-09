#ifndef EYEEXERCISETIME_H
#define EYEEXERCISETIME_H

#include <DWidget>
#include <QLabel>
#include <QLayout>
#include <QEvent>

#include <DAbstractDialog>

DWIDGET_USE_NAMESPACE

class TimeSpinBox;

class EyeExerciseTime : public DWidget
{
public:
    EyeExerciseTime(QWidget *parent = nullptr);

    void initUI();

    void setTime(int hour, int minute, int second);

protected:

    void focusInEvent(QFocusEvent *event)override;

    void focusOutEvent(QFocusEvent *event)override;

    void keyPressEvent(QKeyEvent *event)override;

    void mouseMoveEvent(QMouseEvent *event)override;

    void paintEvent(QPaintEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

private:
    //小时显示
    TimeSpinBox *m_pMinute;
    //冒号：
    QLabel *m_pSecondPoint;
    //分钟显示
    TimeSpinBox *m_pSecond;
    //时间布局
    QHBoxLayout *pTimeLayout;
};

#endif // EYEEXERCISETIME_H
