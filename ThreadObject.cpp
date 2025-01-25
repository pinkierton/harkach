#include "ThreadObject.h"
#include <QVariant>
#include <QDateTime>
#include <QDebug>

ThreadObject::ThreadObject(const QJsonObject &threadObj, QObject *parent)
    :
      QObject(parent),
      mNum(threadObj[QLatin1String("num")].toVariant().toInt()),
      mPostsCount(threadObj[QLatin1String("posts_count")].toInt()),
      mComment(threadObj[QLatin1String("comment")].toString().remove(QLatin1String("\\r\\n"))),
      mSubject(threadObj[QLatin1String("subject")].toString()),
      mTimeStamp(QDateTime::fromSecsSinceEpoch(threadObj[QLatin1String("timestamp")].toVariant().toUInt())),
      mLasthit(QDateTime::fromSecsSinceEpoch(threadObj[QLatin1String("lasthit")].toVariant().toUInt())),
      mFiles(Attachment::makeAttachmentList(threadObj[QLatin1String("files")].toArray(), this))
{
}

ThreadObject::~ThreadObject() {
    qDeleteAll(mFiles);
    mFiles.clear();
}

int ThreadObject::num() const {
    return mNum;
}

void ThreadObject::setNum(int value) {
    if (mNum != value) {
        mNum = value;
        emit numChanged();
    }
}

int ThreadObject::postsCount() const {
    return mPostsCount;
}

void ThreadObject::setPostsCount(int value) {
    if (mPostsCount != value) {
        mPostsCount = value;
        emit postsCountChanged();
    }
}

QString ThreadObject::comment() const {
    return mComment;
}

void ThreadObject::setComment(const QString &value) {
    if (mComment != value) {
        mComment = value;
        emit commentChanged();
    }
}

QString ThreadObject::subject() const {
    return mSubject;
}

void ThreadObject::setSubject(const QString &value) {
    if (mSubject != value) {
        mSubject = value;
        emit subjectChanged();
    }
}

QDateTime ThreadObject::timeStamp() const {
    return mTimeStamp;
}

void ThreadObject::setTimeStamp(QDateTime value) {
    if (mTimeStamp != value) {
        mTimeStamp = value;
        emit timeStampChanged();
    }
}

QDateTime ThreadObject::lasthit() const {
    return mLasthit;
}

void ThreadObject::setLasthit(QDateTime value) {
    if (mLasthit != value) {
        mLasthit = value;
        emit lasthitChanged();
    }
}

AttachmentList ThreadObject::files() const
{
    return mFiles;
}

void ThreadObject::setFiles(const AttachmentList &value)
{
    if (mFiles != value) {
        mFiles = value;
        emit filesChanged();
    }
}






