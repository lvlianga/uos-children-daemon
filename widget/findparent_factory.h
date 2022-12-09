#ifndef FINDPARENTFACTORY_H
#define FINDPARENTFACTORY_H

#include <QWidget>
#include "base_find_parentdialog.h"
#include "../service/httpclient.h"

class FindParentFactory : public QObject
{
    Q_OBJECT
public:
    explicit FindParentFactory(applyType type, int count, QJsonArray array);

    void createFindParentDialog();

    void showFindParentDialog();

signals:

    void signalCloseMianDialog();

public slots:

private:
    applyType m_type;
    int m_count;
    QJsonArray m_array;
    BaseFindParentDialog *m_baseFindParentDialog = nullptr;
};

#endif // FINDPARENTFACTORY_H
