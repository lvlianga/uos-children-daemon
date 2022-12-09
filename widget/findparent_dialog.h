/**
 * @file     findparentdialog.h
 * @brief    去找家长对话框类
 * @author   lvliang
 * @date     2021-11-10
 * @copyright   Copyright (c) 2050
 * @attention
 * QT版本：5.11.3 (GCC 8.3.0, 64 bit)
*/
#ifndef FINDPARENTDIALOG_H
#define FINDPARENTDIALOG_H
#include "../service/httpclient.h"

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QJsonArray>

#include <DSuggestButton>
#include <DAbstractDialog>
#include <DWindowCloseButton>
#include <DTextEdit>
#include <DComboBox>
#include <DMenu>
#include <DToolButton>
#include <DPushButton>
#include <DFloatingMessage>

DWIDGET_USE_NAMESPACE

class FindParentDialog : public DAbstractDialog
{
    Q_OBJECT
public:
    /**
     * @brief FindParentDialog 去找家长对话框
     * @param type 申请的类型
     * @param count 申请的个数
     * @param array 申请的内容
     * @param parent
     * @author lvliang
     * @date 2021-11-10
     */
    explicit FindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent);
    /**
     * @brief setfindParent
     * @param type 请求类型
     * @param count 所有申请应用个数
     * @param array 申请应用内容
     * @author lvliang
     * @date 2021-11-10
     */
    void setfindParent(applyType type, int count, QJsonArray array);

protected:
    //按键事件　鼠标释放弹出菜单
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);

public slots:
    /**
     * @brief slot_cancelsiginal 取消按钮关闭页面
     * @author lvliang
     * @date 2021-11-10
     */
    void slot_cancelsiginal();
    /**
     * @brief slot_sendsignal 点击去找家长
     * @author lvliang
     * @date 2021-11-10
     */
    void slot_sendsignal();
    /**
     * @brief slot_closed 关闭二维码鉴权界面
     * @author lvliang
     * @date 2021-11-10
     */
    void slot_closed();

private: signals:
    /**
     * @brief signal_requestContextMenu
     * @param bClicked
     * @author lvliang
     * @date 2021-11-10
     */
    void signal_requestContextMenu(bool bClicked = false);
    /**
     * @brief signal_applySuccess 发送申请成功的请求
     * @param applySuccess
     * @author lvliang
     * @date 2021-11-10
     */
    void signal_applySuccess(bool applySuccess);
    /**
     * @brief closeMainDialog 发送关闭父界面的窗口的请求
     * @author lvliang
     * @date 2021-11-10
     */
    void closeMainDialog();

private:
    /**
     * @brief initUI 初始化UI
     * @author lvliang
     * @date 2021-11-10
     */
    void initUI();
    /**
     * @brief FindParentDialog::initConnect 初始化信号槽
     * @author lvliang
     * @date 2021-11-10
     */
    void initConnect();
    /**
     * @brief insertMenuQuickReply 插入快捷回复到菜单
     * @param listQuickReply
     * @author lvliang
     * @date 2021-11-10
     */
    void insertMenuQuickReply(const QStringList &listQuickReply);
    /**
     * @brief dataAnalysis 根据不同的类型解析对应的数据
     * @param type 鉴权二维码类型
     * @param array 获取的数据内容
     * @author lvliang
     * @date 2021-11-10
     */
    void dataAnalysis(applyType type, QJsonArray array);
    /**
     * @brief FindParentDialog::setIconAndName 设置图片和名称
     * @param count 个数
     * @param icon 图片
     * @param name 名称
     * @author lvliang
     * @date 2021-11-10
     */
    void setIconAndName(int count, QString icon, QString name);
    /**
     * @brief FindParentDialog::setIcon 设置图片
     * @param count 个数
     * @param icon 图片
     * @author lvliang
     * @date 2021-11-10
     */
    void setIcon(int count, QString icon);
    /**
     * @brief sendInstallData 发送待安装应用数据
     * @param array
     * @author lvliang
     * @date 2021-11-10
     */
    void sendInstallData(QJsonArray array);
    /**
     * @brief sendExternData 发送待延长应用数据
     * @param array
     * @author lvliang
     * @date 2021-11-10
     */
    void sendExternData(QJsonArray array);
    /**
     * @brief setEnable 设置下拉框是否可用
     * @param isEnable true:可用 false:不可用
     * @author lvliang
     * @date 2021-11-10
     */
    void setEnable(bool isEnable);
    /**
     * @brief setshowTips 显示提示界面
     * @param text 提示内容
     * @author lvliang
     * @date 2021-11-10
     */
    void setshowTips(const QString &text);

private:
    QVBoxLayout *m_boxlayout;
    //界面关闭按钮
    DWindowCloseButton *m_closeButton;
    QLabel *m_iconLabel;
    QLabel *m_textLabel;
    QLabel *m_icon;
    QLabel *m_name1;
    QLabel *m_icon1;
    QLabel *m_name2;
    QLabel *m_icon2;
    QLabel *m_icon3;
    QLabel *m_icon4;
    QLabel *labtext;
    DPushButton *m_pushButton1;
    DMenu  *m_menu;
    DTextEdit *m_dtextEdit;
    QLabel *noticeLabel;
    //发送按钮
    DSuggestButton *m_pushButton;
    //通用快捷回复
    QStringList m_listGeneralQuickReply;
    //眼保健操快捷回复
    QStringList m_listEyeExercisesQuickReply;
    //锁屏快捷回复
    QStringList m_listUnLockQuickReply;
    //获取申请解析的数据
    QJsonArray jsonarray;
    //传给http的数据
    QString retVal;
    //显示提示的控件
    DFloatingMessage *m_pTips;
    bool m_bPressed = false;
    bool isRequest = false;
    bool isSendPushButton = false;
    int m_type;
    int m_count;
    QString m_username;
};

#endif // FINDPARENTDIALOG_H
