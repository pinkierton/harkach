#ifndef THREADOBJECT_H
#define THREADOBJECT_H

#include <QDateTime>
#include <QObject>
#include <QQmlListProperty>
#include "Attachment.h"
#include <QDebug>

class ThreadObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(            int num         READ num         WRITE setNum         NOTIFY numChanged        )
    Q_PROPERTY(            int postsCount  READ postsCount  WRITE setPostsCount  NOTIFY postsCountChanged )
    Q_PROPERTY(        QString comment     READ comment     WRITE setComment     NOTIFY commentChanged    )
    Q_PROPERTY(        QString subject     READ subject     WRITE setSubject     NOTIFY subjectChanged    )
    Q_PROPERTY(      QDateTime timeStamp   READ timeStamp   WRITE setTimeStamp   NOTIFY timeStampChanged  )
    Q_PROPERTY(      QDateTime lasthit     READ lasthit     WRITE setLasthit     NOTIFY lasthitChanged    )
    Q_PROPERTY( AttachmentList files       READ files       WRITE setFiles       NOTIFY filesChanged      )
public:
    explicit ThreadObject(QObject *parent = 0) : QObject(parent)
    {
    }

    explicit ThreadObject(const QJsonObject &threadObj, QObject *parent = 0);

    ~ThreadObject();


    int num() const;
    void setNum(int value);

    int postsCount() const;
    void setPostsCount(int value);

    QString comment() const;
    void setComment(const QString &value);

    QString subject() const;
    void setSubject(const QString &value);

    QDateTime timeStamp() const;
    void setTimeStamp(QDateTime value);

    QDateTime lasthit() const;
    void setLasthit(QDateTime value);

    AttachmentList files() const;
    void setFiles(const AttachmentList &value);

private:
    int mNum;
    int mPostsCount;
    QString mComment;
    QString mSubject;
    QDateTime mTimeStamp;
    QDateTime mLasthit;
    AttachmentList mFiles;

signals:
    void numChanged();
    void postsCountChanged();
    void commentChanged();
    void subjectChanged();
    void timeStampChanged();
    void lasthitChanged();
    void filesChanged();

public slots:
};

#endif // THREADOBJECT_H
