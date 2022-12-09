#ifndef THEREMAININGTIMEDIALOG_H
#define THEREMAININGTIMEDIALOG_H

#include <DAbstractDialog>
#include <QSpinBox>

DWIDGET_USE_NAMESPACE

class DIconButton;

class TheRemainingTimeDialog : public QObject
{
    Q_OBJECT
public:
    explicit TheRemainingTimeDialog(QObject *parent = nullptr);

private:
    QSpinBox *m_hour;
    QSpinBox *m_minute;
    QSpinBox *m_second;
};

#endif // THEREMAININGTIMEDIALOG_H
