#include "mode_tips_dialog.h"

#include <QFrame>
#include <QVBoxLayout>

#include <DWidget>

ModeTipsDialog::ModeTipsDialog(QWidget *parent)
    : DAbstractDialog(parent)
    , mtimer(new QTimer(this))
    , mcloseBtn(new DWindowCloseButton(this))
    , miconLabel(new DLabel(this))
    , moneTextLabel(new DLabel(this))
    , mtwoTextLabel(new DLabel(this))
{
    initUI();
    initConnets();
}

void ModeTipsDialog::showType(ModeTipsType type)
{

    switch (type) {
    case FiveMinuteChangeToStudy:
        moneTextLabel->setText(ModeTipsDialog::tr(FiveMinuteChangeToStudyMode));
        mtwoTextLabel->setText(ModeTipsDialog::tr(FiveMinuteChangeToStudyModeLineTwo));
        miconLabel->setPixmap(QPixmap(":/images/light/study.png"));
        break;
    case FiveMinuteChangeToFree:
        moneTextLabel->setText(ModeTipsDialog::tr(FiveMinuteChangeToFreeMode));
        mtwoTextLabel->setText(ModeTipsDialog::tr(FiveMinuteChangeToStudyModeLineTwo));
        miconLabel->setPixmap(QPixmap(":/images/light/free.png"));
        break;
    case FiveMinuteChangeToDisable:
        moneTextLabel->setText(ModeTipsDialog::tr(FiveMinuteChangeToDisableMode));
        mtwoTextLabel->setText(ModeTipsDialog::tr(FiveMinuteChangeToDisableModeLineTwo));
        miconLabel->setPixmap(QPixmap(":/images/light/disable.png"));
        break;
    case ChangeToFree:
        moneTextLabel->setText(ModeTipsDialog::tr(ChangeToFreeMode));
        mtwoTextLabel->setText(" ");
        miconLabel->setPixmap(QPixmap(":/images/light/free.png"));
        break;
    case ChangeToStudy:
        moneTextLabel->setText(ModeTipsDialog::tr(ChangeToStudyMode));
        mtwoTextLabel->setText(" ");
        miconLabel->setPixmap(QPixmap(":/images/light/study.png"));
        break;
    default:
        break;
    }
    mtimer->stop();
    mtimer->start();
    show();
}

void ModeTipsDialog::initUI()
{
    setFixedSize(400, 339);
    setContentsMargins(0, 0, 0, 0);

    mtimer->setInterval(THREE_MINUTE);

    QPalette paBack;
    paBack.setColor(QPalette::Background, Qt::white);

    setPalette(paBack);
    setAutoFillBackground(true);

    // 关闭按钮
    mcloseBtn->setFocusPolicy(Qt::NoFocus);
    mcloseBtn->setIconSize(QSize(30, 30));

    miconLabel->setFixedSize(352, 198);
    miconLabel->setScaledContents(true);

    QFont font16("NotoSansCJKsc");
    font16.setPixelSize(15);
    font16.setWeight(QFont::DemiBold);

    moneTextLabel->setFixedSize(186, 24);
    moneTextLabel->setFont(font16);
    moneTextLabel->setAlignment(Qt::AlignCenter);
    moneTextLabel->setWordWrap(true);

    QFont font14("NotoSansCJKsc");
    font14.setPixelSize(13);
    font14.setWeight(QFont::Normal);

    mtwoTextLabel->setMinimumSize(400, 21);
    mtwoTextLabel->setFont(font14);
    mtwoTextLabel->setAlignment(Qt::AlignCenter);
    mtwoTextLabel->setWordWrap(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addWidget(mcloseBtn, 0, Qt::AlignRight | Qt::AlignTop);
    mainLayout->addWidget(miconLabel, 0, Qt::AlignHCenter | Qt::AlignTop);
    mainLayout->addWidget(moneTextLabel, 0, Qt::AlignHCenter | Qt::AlignTop);
    mainLayout->addSpacing(4);
    mainLayout->addWidget(mtwoTextLabel, 0, Qt::AlignHCenter | Qt::AlignTop);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void ModeTipsDialog::initConnets()
{
    connect(mcloseBtn, &DWindowCloseButton::clicked, this, [ this ]() {
        this->close();
    });

    connect(mtimer, &QTimer::timeout, this, [this]() {
        close();
    });
}
