#include "eyeexercise_time.h"
#include "time_spin_box.h"
#include <QPainter>

#include <QCloseEvent>

EyeExerciseTime::EyeExerciseTime(QWidget *parent)
    : DWidget(parent)
    , m_pMinute(new TimeSpinBox)
    , m_pSecondPoint(new QLabel(":"))
    , m_pSecond(new TimeSpinBox)
    , pTimeLayout(new QHBoxLayout)
{
    initUI();
}

void EyeExerciseTime::initUI()
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    setContentsMargins(0, 0, 0, 0);

    setFixedSize(165, 45);

    QFont font;
    font.setFamily("Noto Sans CJK SC");
    font.setPointSize(24);

    m_pMinute->setFixedSize(64, 40);
    m_pMinute->setRange(0, 59);
    m_pMinute->setSingleStep(1);
    m_pMinute->setWrapping(true);
    m_pMinute->setButtonSymbols(QAbstractSpinBox::NoButtons);
    m_pMinute->setEnabled(false);
    m_pMinute->setFont(font);

    m_pSecondPoint->setFont(font);

    m_pSecond->setFixedSize(64, 40);
    m_pSecond->setRange(0, 59);
    m_pSecond->setSingleStep(1);
    m_pSecond->setWrapping(true);
    m_pSecond->setButtonSymbols(QAbstractSpinBox::NoButtons);
    m_pSecond->setEnabled(false);
    m_pSecond->setFont(font);

    pTimeLayout->setContentsMargins(7, 0, 7, 0);
    pTimeLayout->addStretch();
    pTimeLayout->addWidget(m_pMinute);
    pTimeLayout->addWidget(m_pSecondPoint);
    pTimeLayout->addWidget(m_pSecond);
    pTimeLayout->addStretch();

    setTime(0, 0, 0);

    setLayout(pTimeLayout);
}

void EyeExerciseTime::setTime(int hour, int minute, int second)
{
    Q_UNUSED(hour);
    m_pMinute->setValue(minute);
    m_pSecond->setValue(second);
}

void EyeExerciseTime::focusInEvent(QFocusEvent *event)
{
    return QWidget::focusInEvent(event);
}

void EyeExerciseTime::focusOutEvent(QFocusEvent *event)
{
    return QWidget::focusOutEvent(event);
}

void EyeExerciseTime::mouseMoveEvent(QMouseEvent *event)
{
    return QWidget::mouseMoveEvent(event);
}

void EyeExerciseTime::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);  // 反锯齿;

    QColor btnBrushColor(Qt::white);

    painter.setBrush(btnBrushColor);
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 15, 15);
    QWidget::paintEvent(event);
}

void EyeExerciseTime::closeEvent(QCloseEvent *event)
{
    if (event->spontaneous()) {
        event->ignore();
    } else {
        event->accept();
    }
}
void EyeExerciseTime::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        break;
    default:
        DWidget::keyPressEvent(event);
    }
}
