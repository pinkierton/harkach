#ifndef POSTMODEL_H
#define POSTMODEL_H

#include "PostObject.h"
#include <QAbstractListModel>
#include <QObjectList>
#include <QDebug>

class PostModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PostModel(QObject *parent = nullptr) : QAbstractListModel(parent)
    {

    }

    ~PostModel() {
        qDeleteAll(mPosts);
        mPosts.clear();
    }

    enum PostRoles {
        BannedRole = Qt::UserRole + 1,
        ClosedRole,
        CommentRole,
        DateRole,
        EmailRole,
        FilesRole,
        LasthitRole,
        NameRole,
        NumRole,
        OpRole,
        ParentRole,
        StickyRole,
        SubjectRole,
        TimestampRole,
        TripRole,
        TripTypeRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return mPosts.count();
    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
        if (index.row() < 0 || index.row() >= rowCount())
            return QVariant();

        using PostObjectPtr = PostObject*;
        const PostObjectPtr& post = mPosts.at(index.row());

        if (role == BannedRole)
            return post->banned();

        else if (role == ClosedRole)
            return post->closed();

        else if (role == CommentRole)
            return post->comment();

        else if (role == DateRole)
            return post->date();

        else if (role == EmailRole)
            return post->email();

        else if (role == FilesRole)
            return QVariant::fromValue(post->files());

        else if (role == LasthitRole)
            return post->lasthit();

        else if (role == NameRole)
            return post->name();

        else if (role == NumRole)
            return post->num();

        else if (role == OpRole)
            return post->op();

        else if (role == ParentRole)
            return post->parent();

        else if (role == StickyRole)
            return post->sticky();

        else if (role == SubjectRole)
            return post->subject();

        else if (role == TimestampRole)
            return post->timestamp();

        else if (role == TripRole)
            return post->trip();

        else if (role == TripTypeRole)
            return post->tripType();

        return QVariant();
    }

    void resetPosts() {
        if (!mPosts.empty()) {
            qDeleteAll(mPosts);
            mPosts.clear();
        }
        beginResetModel();
        endResetModel();
    }

    void addPosts(QList<PostObject*>&& threads) {
        qDebug() << Q_FUNC_INFO;

        int pos = mPosts.count();

        beginInsertRows(QModelIndex(), pos , pos + threads.count() - 1);
        if (mPosts.isEmpty()) {
            mPosts = threads;
        } else {
            mPosts << threads;
        }
        endInsertRows();
    }

    const QList<PostObject*> &getPosts() const noexcept {
        return mPosts;
    }

protected:
    QHash<int, QByteArray> roleNames() const override {
        return {
            {BannedRole,    "banned"   },
            {ClosedRole,    "closed"   },
            {CommentRole,   "comment"  },
            {DateRole,      "date"     },
            {EmailRole,     "email"    },
            {FilesRole,     "files"    },
            {LasthitRole,   "lasthit"  },
            {NameRole,      "name"     },
            {NumRole,       "num"      },
            {OpRole,        "op"       },
            {ParentRole,    "parent"   },
            {StickyRole,    "sticky"   },
            {SubjectRole,   "subject"  },
            {TimestampRole, "timestamp"},
            {TripRole,      "trip"     },
            {TripTypeRole,  "trip_type"}
        };
    }

private:
    QList<PostObject*> mPosts;


signals:

public slots:
};

#endif // POSTMODEL_H
