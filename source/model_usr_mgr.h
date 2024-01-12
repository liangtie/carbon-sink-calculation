#ifndef MODEL_USR_MGR_H
#define MODEL_USR_MGR_H

#include <QAbstractTableModel>
#include <memory>
#include <vector>

#include <qabstractitemmodel.h>
#include <qobject.h>
#include "usr_info.h"
struct AddUserForm;

class ModelUserMgr : public QAbstractTableModel
{
    Q_OBJECT
  public:
    enum Cols
    {
        NAME,
        ROLE ,
        COL_COUNT
    };

    ModelUserMgr(QObject* parent = nullptr);
    ~ModelUserMgr();

    void setUsers(UserInfoList user_list);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant data(const QModelIndex& index,
                  int role = Qt::DisplayRole) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    auto getUsrInfo(int row){
        return _user_list[row] ;
    }

  private:
    UserInfoList _user_list;
};

#endif