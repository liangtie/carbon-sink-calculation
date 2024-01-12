#include "model_usr_mgr.h"

#include <qabstractitemmodel.h>
#include <qnamespace.h>
#include <qtpreprocessorsupport.h>

#include "dialog_add_new_user.h"
#include "usr_info.h"

ModelUserMgr::ModelUserMgr(QObject* parent)
    : QAbstractTableModel(parent)
{
}

ModelUserMgr::~ModelUserMgr() {}

void ModelUserMgr::rmUser(int row) {}

void ModelUserMgr::updateUserPassword(int row) {}

void ModelUserMgr::setUsers(UserInfoList user_list)
{
    beginResetModel();
    _user_list = std::move(user_list);
    endResetModel();
}

Qt::ItemFlags ModelUserMgr::flags(const QModelIndex& index) const
{
    Q_UNUSED(index)

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ModelUserMgr::data(const QModelIndex& index, int role) const
{

    const auto current = _user_list[index.row()];
    switch (role) {
        case Qt::DisplayRole:
        case Qt ::ToolTipPropertyRole:
        case Qt::StatusTipPropertyRole:
            switch (index.column()) {
                case NAME:
                    return QString::fromStdString(current.name);
                case ROLE:
                    return current.role == "3" ? "普通用户" : "管理员";
            }
    }

    return {};
}

QVariant ModelUserMgr::headerData(int section,
                                  Qt::Orientation orientation,
                                  int role) const
{
    if (Qt::TextAlignmentRole == role)
        return Qt::AlignCenter;

    if (Qt::Orientation::Horizontal == orientation && Qt::DisplayRole == role) {
        switch (section) {
            case NAME:
                return "用户名称";
            case ROLE:
                return "用户角色";
        }
    }
    return {};
}

int ModelUserMgr::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    if (parent.isValid())
        return 0;

    return _user_list.size();
}

int ModelUserMgr::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return COL_COUNT;
}
