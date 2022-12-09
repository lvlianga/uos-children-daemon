#include "eyeexercises_widget.h"

#include <QVideoWidget>
#include <QUrl>
#include <QDebug>
#include <QCloseEvent>
#include <QGuiApplication>
#include <QScreen>

#include "quit_button.h"
#include "eyeexercise_time.h"

EyeExercisesWidget::EyeExercisesWidget(QWidget *parent)
    : QWidget(parent)
    , m_quitIcon(new QuitButton(this))
    , m_eyeTime(new EyeExerciseTime(this))
{
    initUi();
}

EyeExercisesWidget::~EyeExercisesWidget()
{
    qInfo() << __FUNCTION__;
    m_quitIcon->close();
    delete m_quitIcon;
    m_quitIcon = nullptr;

    player->stop();
    delete player;
    player = nullptr;

    m_eyeTime->close();
    delete m_eyeTime;
    m_eyeTime = nullptr;

    delete vw;
    vw = nullptr;
}

qint64 EyeExercisesWidget::getVideoDurationTime()
{
    return m_videoTime;
}

void EyeExercisesWidget::reSetVWSize()
{
    vw->setFixedSize(qApp->primaryScreen()->size());
}

void EyeExercisesWidget::initUi()
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool);
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);


    QMediaContent mc(QUrl::fromLocalFile(EYE_EXERCISES_PATH));
    if (false == mc.isNull()) {
        initConnect();
        player->setMedia(mc);
        player->setVideoOutput(vw);
        player->play();
    }

    m_quitIcon->show();
    removeExitDialog();

    m_eyeTime->show();
    removeEyeDialog();

    QVBoxLayout *grid = new QVBoxLayout(this);

    grid->addWidget(vw, 0, Qt::AlignCenter);

    grid->setContentsMargins(0, 0, 0, 0);
    setLayout(grid);
}

void EyeExercisesWidget::initConnect()
{
    connect(m_quitIcon, &QuitButton::signals_enter, this, &EyeExercisesWidget::closeEyeExercise);
    connect(player, &QMediaPlayer::positionChanged, this, &EyeExercisesWidget::signal_playTimeChange);
    connect(player, &QMediaPlayer::positionChanged, this, &EyeExercisesWidget::slot_changeTimeDialogTime);
    connect(player, &QMediaPlayer::stateChanged, this, &EyeExercisesWidget::signal_stateChanged);
}

void EyeExercisesWidget::closeEyeExercise()
{
    emit signalCloseEyeCare();
    this->close();
}

void EyeExercisesWidget::removeExitDialog()
{
    QScreen *mainScreen = qApp->primaryScreen();
    QRect rect = mainScreen->geometry();
    int width = rect.width();
    //240, 164
    m_quitIcon->move(width + rect.left() - 250, 100);
}

void EyeExercisesWidget::removeEyeDialog()
{
    QScreen *mainScreen = qApp->primaryScreen();
    QRect rect = mainScreen->geometry();
    int width = rect.width();
    int height = rect.height();
    //240, 164
    m_eyeTime->move(width + rect.left() - 250, height - 164);
}

void EyeExercisesWidget::closeEvent(QCloseEvent *event)
{
    if (event->spontaneous()) {
        event->ignore();
    } else {
        event->accept();
    }
}

void EyeExercisesWidget::slot_changeTimeDialogTime(qint64 time)
{
    m_videoTime = player->duration();
    time = m_videoTime - time;
    int ss = 1000;
    int mi = ss * 60;
    int hh = mi * 60;
    int dd = hh * 24;

    long day = time / dd;
    long hour = (time - day * dd) / hh;
    long minute = (time - day * dd - hour * hh) / mi;
    long second = (time - day * dd - hour * hh - minute * mi) / ss;

//    m_pTimeDialog->setTime(hour, minute, second);

    m_eyeTime->setTime(static_cast<int >(hour), static_cast<int>(minute), static_cast<int>(second));
}
