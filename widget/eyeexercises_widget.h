/*
*眼保健操窗口
*/

#ifndef EYEEXERCISESWIDGET_H
#define EYEEXERCISESWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QLayout>

class EyeExerciseTime;
class QuitButton;

class EyeExercisesWidget : public QWidget
{
    Q_OBJECT
public:
    EyeExercisesWidget(QWidget *parent = nullptr);
    ~EyeExercisesWidget();
    /**
     * @brief getVideoDurationTime 获取视频播放持续时间
     * @return
     */
    qint64 getVideoDurationTime();
    /**
     * @brief reSetVWSize 重新设置播放器大小
     * @author : liudongyu
     * @date : 2022/01/26
     */
    void reSetVWSize();

protected:
    void closeEvent(QCloseEvent *event);

private:
    /**
     * @brief initUi              初始化UI
     * @author : liudongyu
     * @date : 2022/01/26
     **/
    void initUi();
    /**
     * @brief initConnect 初始化信号槽
     * @author : liudongyu
     * @date : 2022/01/26
     */
    void initConnect();

    void closeEyeExercise();

    void removeExitDialog();

    void removeEyeDialog();

signals:
    /**
     * @brief signal_playTimeChange 播放时间改变信号
     * @author : liudongyu
     * @date : 2022/01/26
     */
    void signal_playTimeChange(qint64);
    /**
     * @brief signal_durationChanged 返回视频总的时间
     * @author : liudongyu
     * @date : 2022/01/26
     */
    void signal_durationChanged(qint64);
    /**
     * @brief signal_stateChanged 视频结束
     * @param newState
     * @author : liudongyu
     * @date : 2022/01/26
     */
    void signal_stateChanged(QMediaPlayer::State newState);

    void signalCloseEyeCare();

public slots:
    /**
     * @brief slot_changeTimeDialogTime 右下角计时变化
     * @param time
     * @author : liudongyu
     * @date : 2022/01/26
     */
    void slot_changeTimeDialogTime(qint64 time);

private:
    //退出按钮
    QuitButton *m_quitIcon = nullptr;
    //眼保健操右下角计时对话框
    EyeExerciseTime *m_eyeTime = nullptr;
    //视频播放器
    QMediaPlayer *player = nullptr;
    //视频播放控件
    QVideoWidget *vw = nullptr;
    //视频播放的时间
    qint64 m_videoTime;
};

#endif // EYEEXERCISESWIDGET_H
