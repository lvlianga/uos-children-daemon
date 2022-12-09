#include "ancient_poems.h"

#include <DLabel>
#include <QHBoxLayout>
#include <DCommandLinkButton>
#include <QCloseEvent>

AncientPoems::AncientPoems()
{
    QPalette pa;
    pa.setColor(QPalette::Background, Qt::white);

    QFrame *frame = new QFrame(this);
    frame->setFixedSize(460, 360);
    frame->setPalette(pa);
    frame->setAutoFillBackground(true);

    DLabel *picLabel = new DLabel(this);
    picLabel->setFixedSize(300, 190);
    picLabel->setScaledContents(true);
    picLabel->setPixmap(QPixmap(":/images/light/overtime.png"));
    QHBoxLayout *picLabelLayout = new QHBoxLayout;
    picLabelLayout->addStretch();
    picLabelLayout->addWidget(picLabel);
    picLabelLayout->addStretch();

    QFont font1("NotoSansCJKsc");
    font1.setPixelSize(15);
    font1.setWeight(QFont::DemiBold);

    QFont font2("NotoSansCJKsc");
    font2.setPixelSize(13);
    font2.setWeight(QFont::Normal);

    DLabel *textLabel = new DLabel(this);
    textLabel->setMinimumSize(240, 22);
    textLabel->setText(tr("根据家长设置，现已到电脑禁用时段"));
    textLabel->setFont(font1);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setWordWrap(true);
    QHBoxLayout *textLabelLayout = new QHBoxLayout;
    textLabelLayout->addWidget(textLabel, 0, Qt::AlignHCenter);

    DCommandLinkButton *btn = new DCommandLinkButton(tr("家长解锁"), this);
    btn->setMinimumSize(52, 19);
    btn->setFont(font2);
    connect(btn, &DCommandLinkButton::clicked, this, &AncientPoems::slot_ApplyForUnlockDesktop);
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(btn, 0, Qt::AlignHCenter);

    QVBoxLayout *frameLayout = new QVBoxLayout;
    frameLayout->setContentsMargins(0, 30, 0, 40);
    frameLayout->setSpacing(0);
    frameLayout->addLayout(picLabelLayout);
    frameLayout->addSpacing(40);
    frameLayout->addLayout(textLabelLayout);
    frameLayout->addSpacing(8);
    frameLayout->addLayout(btnLayout);
    frameLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(frameLayout);
    mainLayout->addStretch();
}

void AncientPoems::closeEvent(QCloseEvent *event)
{
    if (event->spontaneous()) {
        event->ignore();
    } else {
        event->accept();
    }
}

void AncientPoems::slot_ApplyForUnlockDesktop()
{
    emit signal_ApplyForUnlockDesktop("");
}
