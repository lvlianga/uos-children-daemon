#ifndef BASEFINDPARENTDIALOG_H
#define BASEFINDPARENTDIALOG_H

#include <QWidget>
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

class BaseFindParentDialog : public DAbstractDialog
{
    Q_OBJECT
public:
    explicit BaseFindParentDialog(applyType type, int count, QJsonArray array, QWidget *parent);

    /**
     * @brief initUI 初始化UI
     * @author lvliang
     * @date 2021-11-10
     */
    virtual void initUI();

public slots:
    /**
     * @brief slot_sendsignal 点击去找家长
     * @author lvliang
     * @date 2021-11-10
     */
    virtual void slot_sendsignal();
    /**
     * @brief slot_closed 关闭二维码鉴权界面
     * @author lvliang
     * @date 2021-11-10
     */
    virtual void slot_closed();

protected:
    /**
     * @brief dataAnalysis 根据不同的类型解析对应的数据
     * @param type 鉴权二维码类型
     * @param array 获取的数据内容
     * @author lvliang
     * @date 2021-11-10
     */
    virtual void dataAnalysis(applyType type, QJsonArray array) = 0;

    virtual void insertMenuQuickReply(const QStringList &listQuickReply);

    /**
     * @brief FindParentDialog::setIcon 设置图片
     * @param count 个数
     * @param icon 图片
     * @author lvliang
     * @date 2021-11-10
     */
    void setIcon(int count, QString icon);

    void setshowTips(const QString &text);

    /**
     * @brief FindParentDialog::initConnect 初始化信号槽
     * @author lvliang
     * @date 2021-11-10
     */
    virtual void initConnect();
    /**
     * @brief setEnable 设置下拉框是否可用
     * @param isEnable true:可用 false:不可用
     * @author lvliang
     * @date 2021-11-10
     */
    virtual void setEnable(bool isEnable);

    //按键事件　鼠标释放弹出菜单
    virtual void closeEvent(QCloseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);


protected: signals:
    /**
     * @brief closeMainDialog 发送关闭父界面的窗口的请求
     * @author lvliang
     * @date 2021-11-10
     */
    virtual void closeMainDialog();

protected:
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
    //获取申请解析的数据
    QJsonArray jsonarray;
    //传给http的数据
    QString retVal;
    //显示提示的控件
    DFloatingMessage *m_pTips;
    applyType m_type;
    int m_count;
    QJsonArray m_array;

    bool isSendPushButton = false;
    QString m_username;
};

#endif // BASEFINDPARENTDIALOG_H
