#include "BoardModel.h"
#include <QDebug>

BoardModel::BoardModel(QObject *parent) : QAbstractListModel(parent)
{
}

BoardModel::~BoardModel() {
    qDeleteAll(mBoards);
    mBoards.clear();
}

QHash<int, QByteArray> BoardModel::roleNames() const {
    return {
        { IdRole,               "board_id"          },
        { NameRole,             "name"              },
        { CategoryRole,         "category"          },
        { DefaultNameRole,      "default_name"      },
        { BumpLimitRole,        "bump_limit"        },
        { PagesRole,            "pages"             },
        { EnableLikesRole,      "enable_likes"      },
        { EnablePostingRole,    "enable_posting"    },
        { EnableThreadTagsRole, "enable_thread_tags"},
        { SageRole,             "sage"              },
        { TripcodesRole,        "tripcodes"         }
    };
}

int BoardModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return mBoards.count();
}

QVariant BoardModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    using BoardPtr = Board*;

    const BoardPtr &board = mBoards.at(index.row());

    if (role == IdRole)
        return board->id();
    else if (role == NameRole)
        return board->name();
    else if (role == CategoryRole)
        return board->category();
    else if (role == DefaultNameRole)
        return board->defaultName();
    else if (role == BumpLimitRole)
        return board->bumpLimit();
    else if (role == PagesRole)
        return board->pages();
    else if (role == EnableLikesRole)
        return board->enableLikes();
    else if (role == EnablePostingRole)
        return board->enablePosting();
    else if (role == EnableThreadTagsRole)
        return board->enableThreadTags();
    else if (role == SageRole)
        return board->sage();
    else if (role == TripcodesRole)
        return board->tripcodes();

    return QVariant();
}

void BoardModel::setBoards(QList<Board *> &&boards) {
    if (!mBoards.empty()) {
        qDeleteAll(mBoards);
        mBoards.clear();
    }
    mBoards = boards;

    beginInsertRows(QModelIndex(), 0, 0+rowCount()-1);
    endInsertRows();
}

const QList<Board *> &BoardModel::getBoards() const noexcept {
    return mBoards;
}
