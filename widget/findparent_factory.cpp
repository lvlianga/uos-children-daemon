#include "findparent_factory.h"
#include "appextern_find_parentdialog.h"
#include "appwhite_find_parentdialog.h"
#include "cancelforbiddon_find_parentdialog.h"
#include "applybrowser_find_parentdialog.h"
#include "unlockdesktop_find_parentdialog.h"

FindParentFactory::FindParentFactory(applyType type, int count, QJsonArray array)
    : QObject()
    , m_type(type)
    , m_count(count)
    , m_array(array)
{
    createFindParentDialog();
    connect(m_baseFindParentDialog, &BaseFindParentDialog::closeMainDialog, this, &FindParentFactory::signalCloseMianDialog);
}

void FindParentFactory::createFindParentDialog()
{
    switch (m_type) {
    case ExtendApply:
        m_baseFindParentDialog = new AppExternFindParentDialog(m_type, m_count, m_array);
        break;
    case ApplyWhite:
        m_baseFindParentDialog = new AppWhiteFindParentDialog(m_type, m_count, m_array);
        break;
    case ApplyCancelForbidden:
        m_baseFindParentDialog = new CancelForbiddonFindParentDialog(m_type, m_count, m_array);
        break;
    case ApplyBrowser:
        m_baseFindParentDialog = new ApplyBrowserFindParentDialog(m_type, m_count, m_array);
        break;
    case UnLockDesktop:
        m_baseFindParentDialog = new UnLockDesktopFindParentDialog(m_type, m_count, m_array);
        break;
    default:
        break;
    }
}

void FindParentFactory::showFindParentDialog()
{
    m_baseFindParentDialog->initUI();
    m_baseFindParentDialog->show();
}


