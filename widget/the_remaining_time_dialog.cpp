#include "the_remaining_time_dialog.h"

TheRemainingTimeDialog::TheRemainingTimeDialog(QObject *parent) : QObject(parent)
{
    m_hour = new QSpinBox;
    m_minute = new QSpinBox;
    m_second = new QSpinBox;
}
