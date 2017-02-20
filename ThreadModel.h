#ifndef THREADMODEL_H
#define THREADMODEL_H

#include "ThreadObject.h"
#include <QAbstractListModel>
#include <QDebug>
#include <QObjectList>
#include <QQmlListProperty>

class ThreadModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ThreadModel(QObject *parent = nullptr) : QAbstractListModel(parent)
    {

    }
    ~ThreadModel() {
        qDeleteAll(mThreads);
        mThreads.clear();
    }

    enum ThreadRoles {
        NumRole = Qt::UserRole + 1,
        PostsCountRole,
        CommentRole,
        SubjectRole,
        TimeStampRole,
        LasthitRole,
        FilesRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return mThreads.count();
    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
        if (index.row() < 0 || index.row() >= rowCount())
            return QVariant();

        using ThreadObjectPtr = ThreadObject*;
        const ThreadObjectPtr& thread = mThreads.at(index.row());

        if (role == NumRole)
            return thread->num();

        else if (role == PostsCountRole)
            return thread->postsCount();

        else if (role == CommentRole)
            return thread->comment();

        else if (role == SubjectRole)
            return thread->subject();

        else if (role == TimeStampRole)
            return thread->timeStamp();

        else if (role == LasthitRole)
            return thread->lasthit();
        else if (role == FilesRole) {
            QObjectList files;
            for (Attachment* att : thread->files()) {
                files << att;
            }

            return QVariant::fromValue(files);
        }

        return QVariant();
    }

    void resetThreads() {
        if (!mThreads.empty()) {
            qDeleteAll(mThreads);
            mThreads.clear();
        }
        beginResetModel();
        endResetModel();
    }

    void setThreads(QList<ThreadObject*>&& threads) {
        mThreads = threads;
        beginInsertRows(QModelIndex(), 0, 0+rowCount()-1);
        endInsertRows();
    }

protected:
    QHash<int, QByteArray> roleNames() const override {
        return {
            {NumRole,        "post_num"   },
            {PostsCountRole, "posts_count"},
            {CommentRole,    "comment"    },
            {SubjectRole,    "subject"    },
            {TimeStampRole,  "time_stamp" },
            {LasthitRole,    "lasthit"    },
            {FilesRole,      "files"      }
        };
    }

private:
    QList<ThreadObject*> mThreads;
};

#endif // THREADMODEL_H
