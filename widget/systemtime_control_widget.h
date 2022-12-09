#ifndef SYSTEMTIMECONTROLWIDGET_H
#define SYSTEMTIMECONTROLWIDGET_H

#include <DWidget>
#include <DAbstractDialog>
#include <com_deepin_daemon_keybinding.h>
#include <com_deepin_wm.h>

#include <QX11Info>

using KeybingdingInter = com::deepin::daemon::Keybinding;
using WM = com::deepin::wm;

DWIDGET_USE_NAMESPACE

class WhiteDialog : public DAbstractDialog
{
    Q_OBJECT
public:
    explicit WhiteDialog(QWidget *parent = nullptr);
    ~WhiteDialog() override;

    void showWindow();

    void closeWindow();

protected:
    void focusOutEvent(QFocusEvent *e)override;

    void closeEvent(QCloseEvent *event);

    void keyPressEvent(QKeyEvent *event);
signals:
    void sigParentUnlock();

private:
    void licenseWin();

    bool showstatus = false;

    WM *m_pWm;

    int m_currentWorkspace;
};

class QGraphicsBlurEffect;
class SystemTimeControlWidget : public DWidget
{
    Q_OBJECT
public:
    static SystemTimeControlWidget *instance();
    ~SystemTimeControlWidget() override;

    void showWidget();

    void closeWidget();

protected:
    void closeEvent(QCloseEvent *event);

private:
    explicit SystemTimeControlWidget(QWidget *parent = nullptr);

    QString queryKeyBind(const QString &id, int type);

    void setKeyBind(const QString &id, int type, const QString &keystroke);

    void setAllKeyEmpty();

    void setLastKey();

    //函数的名称和实现都是按照dtk中复制，如实dtk项目生成的窗口可直接调用此函数
    xcb_atom_t internAtom(const char *name, bool only_if_exists = true);

    xcb_atom_t internAtom(xcb_connection_t *connection, const char *name, bool only_if_exists);

    /**
     * @brief sendWindowMove
     * @param WId   窗口ID，如果是qt创建的窗口，此处添加this->winID,
     *              如果是DTK窗口，此参数为父窗口ID（参考qt5platform-plugin源码实现）
     * @param globalPos 移动的目标位置信息
     * @param forhibit  禁止窗口移动，用于鼠标抬起等事件到来时使用
     */
    void sendWindowMove(quint32 WId, int desktop);

signals:
    void sigParentUnlock();

private:
    QGraphicsBlurEffect *graphicEffect;
    WhiteDialog *m_dialog = nullptr;
    KeybingdingInter *m_keybindInter;
    bool showstatus = false;
    QString m_moveToWorkspaceLeft;//super shift left  move-to-workspace-left
    QString m_moveToWorkspaceRight;//super shift right  move-to-workspace-right
    QString m_previewWorkspace;//super s preview-workspace
    QString m_exposeWindows;//super expose-windows
    QString m_exposeAllWindows;//super a expose-all-windows
    QString m_activateWindowMenu;//alt space activate-window-menu
    QString m_launcher;//super launcher
};

#endif // SYSTEMTIMECONTROLWIDGET_H
