/**
 * @file     curtainwidget.h
 * @brief    锁屏界面类
 * @author   lvliang
 * @date     2022-03-13
 * @copyright   Copyright (c) 2050
 * @attention
 * QT版本：5.11.3 (GCC 8.3.0, 64 bit)
*/
#ifndef CURTAINWIDGET_H
#define CURTAINWIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QMap>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QMediaPlayer>

enum ClickType {
    letfMode = 0,
    rightMode
};

class custombutton;
class UnLockButton;
class QuitButton;
class QGraphicsBlurEffect;
class EyeExercisesWidget;

class CurtainWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief CurtainWidget 桌面锁屏界面
     * @param rect
     * @param parent
     * @author lvliang
     * @date 2022-03-13
     * @attention
     */
    explicit CurtainWidget(QRect rect, QWidget *parent = nullptr);

    ~CurtainWidget();
    /**
     * @brief initUI 初始化界面
     * @author lvliang
     * @date 2022-03-13
     * @attention
     */
    void initUI();
    /**
     * @brief initConnect 初始化信号槽
     * @author lvliang
     * @date 2022-03-13
     */
    void initConnect();
    /**
     * @brief updateTime 更新时间
     * @author lvliang
     * @date 2022-03-13
     */
    void updateTime();
    /**
     * @brief unLockDesktop 打开解锁二维码
     * @author lvliang
     * @date 2022-03-13
     */
    void unLockDesktop();
    /**
     * @brief quitDesktop 退出锁屏页面
     */
    void quitDesktop();
    /**
     * @brief randomData 设置背景图片写入
     * @author lvliang
     * @date 2022-03-13
     */
    void randomData();
    /**
     * @brief drawImage 返回图片
     * @param path 需要给的图片路径
     * @return 返回一个QImage的图片
     * @author lvliang
     * @date 2022-03-13
     */
    QImage drawImage(QString path);    // 设置图片列表;
    /**
     * @brief addImage 添加图片到容器中
     * @param imageFileName QImage的图片
     * @author lvliang
     * @date 2022-03-13
     */
    void addImage(QImage imageFileName);
    /**
     * @brief clearList 清空容器
     * @author lvliang
     * @date 2022-03-13
     */
    void clearList();
    /**
     * @brief setCurrentIndex 设置当前显示的图片
     * @param index 图片的标号
     * @author lvliang
     * @date 2022-03-13
     */
    void setCurrentIndex(int index);
    /**
     * @brief setPreIndex 设置上一张图片
     * @param index 图片的标号
     * @author lvliang
     * @date 2022-03-13
     */
    void setPreIndex(int index);
    /**
     * @brief setPreIndex 设置下一张图片
     * @param index 图片的标号
     * @author lvliang
     * @date 2022-03-13
     */
    void setNextIndex(int index);

    void startPlay();

    void setUIType(int type);

    void openEyeExercise();

    void closeEyeCare();

signals:
    /**
     * @brief signal_sendUnlock 发送信号解锁信号
     * @param id 解锁信号的id值
     * @author lvliang
     * @date 2022-03-13
     */
    void signal_sendUnlock(QString id);

    void signal_sendQuitDesktop(QString id);

    void signalOpenEyeCare();

private slots:
    /**
     * @brief onImageLeftButtonClicked 图片左侧切换按钮点击
     * @author lvliang
     * @date 2022-03-13
     */
    void onImageLeftButtonClicked();
    /**
     * @brief onImageRightButtonClicked 图片右侧切换按钮点击
     * @author lvliang
     * @date 2022-03-13
     */
    void onImageRightButtonClicked();
    /**
     * @brief setUnLockPushButton 解锁图标按钮可用
     * @author lvliang
     * @date 2022-03-13
     */
    void setUnLockPushButton();

    void onImageChangeTimeout();

    void slotPlayTimeChange(qint64 position);

    void slotStateChanged(QMediaPlayer::State newState);

protected:
    /**
     * @brief paintEvent 桌面锁屏壁纸
     * @param event
     * @author lvliang
     * @date 2022-03-13
     */
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    QGraphicsBlurEffect *m_graphicEffect = nullptr;
    EyeExercisesWidget *m_eyeExerciseWidget = nullptr;
    QTimer *m_timer = nullptr; //计时器
    QTimer m_imageChangeTimer;
    QWidget *m_mainWidget = nullptr;
    QuitButton *m_quitIcon = nullptr;
    QWidget *m_topWidget = nullptr;
    QWidget *m_centerWidget = nullptr;
    UnLockButton *m_exeiseButton = nullptr; //播放眼保健操按钮
    UnLockButton *m_unLockButton = nullptr; //我要解锁按钮
    QHBoxLayout *m_quitLayout = nullptr; //退出按钮布局
    QVBoxLayout *m_topLayout = nullptr; //顶部时间布局
    QHBoxLayout *m_midLayout = nullptr; //左右切换按钮
    QHBoxLayout *m_hButtonLayout = nullptr; //轮播按钮布局
    QVBoxLayout *m_mainLayout = nullptr;
    QList<QImage> m_imageList;// 图片列表
    int m_preDrawImageIndex = 0; // 上一张显示图片index
    int m_currentDrawImageIndex = 0;// 当前显示图片index
    int m_nextDrawImageIndex = 0; // 下一张显示图片index
    QPixmap m_prePixmap;// 当前图片
    QPixmap m_currentPixmap;// 当前图片
    QPixmap m_nextPixmap;// 下一张图片
    QPixmap m_theNextPixmap;//paint画图时切换的下一张图片
    QPixmap m_theCurrentPixmap;//paint画图时切换的当前图片
    custombutton *m_pLeftButton = nullptr; // 左侧切换按钮
    custombutton *m_pRightButton = nullptr; // 右侧切换按钮
    QMap<int, QJsonObject> m_map;//key是当前片的m_currentDrawImageIndex;value是古诗词
    //时间lab
    QLabel *m_timelab;
    //日期lab
    QLabel *m_datelab;
    //获取当前用户名
    QString m_username;
    QList<int> lst;
    //图片切换动画类;
    QPropertyAnimation *m_opacityAnimation = nullptr;
    //记录当前屏幕宽度
    int currentWidth;
    //记录当前屏幕高度
    int currentHeight;
    //点击左右按钮
    int isLeftToRight = 0;//默认初始值为0,点击左侧为1,点击右侧为2
};

#endif // CURTAINWIDGET_H
