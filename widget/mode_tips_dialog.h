#ifndef MODETIPSDIALOG_H
#define MODETIPSDIALOG_H

#include <QTimer>

#include <DAbstractDialog>

#include <DWindowCloseButton>
#include <DLabel>

#include "public_data_and_struct.h"

DWIDGET_USE_NAMESPACE

class ModeTipsDialog : public DAbstractDialog
{
    Q_OBJECT
public:
    ModeTipsDialog(QWidget *parent = nullptr);

    void showType(ModeTipsType type);
private:
    void initUI();

    void initConnets();
private:
    QTimer *mtimer = nullptr;
    DWindowCloseButton *mcloseBtn = nullptr;
    DLabel *miconLabel = nullptr;
    DLabel *moneTextLabel = nullptr;
    DLabel *mtwoTextLabel = nullptr;
};

#endif // MODETIPSDIALOG_H
