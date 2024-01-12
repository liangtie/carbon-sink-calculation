#include "model_usr_mgr.h"

#include <qabstractitemmodel.h>
#include <qnamespace.h>
#include <qtpreprocessorsupport.h>

#include "dialog_add_new_user.h"

ModelUserMgr::ModelUserMgr(QObject* parent)
    : QAbstractTableModel(parent)
{
}

ModelUserMgr::~ModelUserMgr() {}

void ModelUserMgr::addUser(AddUserForm const& usr) {}

void ModelUserMgr::rmUser(int row) {}

void ModelUserMgr::updateUserPassword(int row) {}

void ModelUserMgr::setUsers(UserInfoList user_list) {
    beginResetModel();
    _user_list = std::move(user_list);
    endResetModel();
}

Qt::ItemFlags ModelUserMgr::flags(const QModelIndex& index) const {
    Q_UNUSED(index)

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ModelUserMgr::data(const QModelIndex& index, int role) const {}

QVariant ModelUserMgr::headerData(int section,
                                  Qt::Orientation orientation,
                                  int role) const
{
    if (Qt::TextAlignmentRole == role)
        return Qt::AlignCenter;

    if (Qt::Orientation::Horizontal == orientation) {
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
    return _user_list.size();
}

int ModelUserMgr::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return COL_COUNT;
}
