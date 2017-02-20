#include "PostObject.h"
#include <QDebug>

PostObject::PostObject(QObject *parent) : QObject(parent)
{

}

PostObject::PostObject(const QJsonObject &postObj, QObject *parent)
    :
      QObject(parent),
      mBanned(static_cast<bool>(postObj[QLatin1String("banned")].toInt())),
      mClosed(static_cast<bool>(postObj[QLatin1String("closed")].toInt())),
      mComment(postObj[QLatin1String("comment")].toString()),
      mDate(postObj[QLatin1String("date")].toString()),
      mEmail(postObj[QLatin1String("email")].toString()),
      mFiles(Attachment::makeObjectList(postObj[QLatin1String("files")].toArray())),
      mLasthit(QDateTime::fromTime_t(postObj[QLatin1String("lasthit")].toVariant().toUInt())),
      mName(postObj[QLatin1String("name")].toString()),
      mNum(postObj[QLatin1String("num")].toVariant().toInt()),
      mOp(static_cast<bool>(postObj[QLatin1String("op")].toInt())),
      mParent(postObj[QLatin1String("parent")].toVariant().toInt()),
      mSticky(static_cast<bool>(postObj[QLatin1String("sticky")].toInt())),
      mSubject(postObj[QLatin1String("subject")].toString()),
      mTimestamp(QDateTime::fromTime_t(postObj[QLatin1String("timestamp")].toVariant().toUInt())),
      mTrip(postObj[QLatin1String("trip")].toString()),
      mTripType(postObj[QLatin1String("trip_type")].toString())
{
}

bool PostObject::banned() const {
    return mBanned;
}

void PostObject::setBanned(bool value) {
    if (mBanned != value) {
        mBanned = value;
        emit bannedChanged();
    }
}
bool PostObject::closed() const {
    return mClosed;
}

void PostObject::setClosed(bool value) {
    if (mClosed != value) {
        mClosed = value;
        emit closedChanged();
    }
}
QString PostObject::comment() const {
    return mComment;
}

void PostObject::setComment(const QString &value) {
    if (mComment != value) {
        mComment = value;
        emit commentChanged();
    }
}
QString PostObject::date() const {
    return mDate;
}

void PostObject::setDate(const QString &value) {
    if (mDate != value) {
        mDate = value;
        emit dateChanged();
    }
}
QString PostObject::email() const {
    return mEmail;
}

void PostObject::setEmail(const QString &value) {
    if (mEmail != value) {
        mEmail = value;
        emit emailChanged();
    }
}
QObjectList PostObject::files() const {
    return mFiles;
}

void PostObject::setFiles(QObjectList value) {
    if (mFiles != value) {
        mFiles = value;
        emit filesChanged();
    }
}
QDateTime PostObject::lasthit() const {
    return mLasthit;
}

void PostObject::setLasthit(QDateTime value) {
    if (mLasthit != value) {
        mLasthit = value;
        emit lasthitChanged();
    }
}
QString PostObject::name() const {
    return mName;
}

void PostObject::setName(const QString &value) {
    if (mName != value) {
        mName = value;
        emit nameChanged();
    }
}
int PostObject::num() const {
    return mNum;
}

void PostObject::setNum(int value) {
    if (mNum != value) {
        mNum = value;
        emit numChanged();
    }
}
bool PostObject::op() const {
    return mOp;
}

void PostObject::setOp(bool value) {
    if (mOp != value) {
        mOp = value;
        emit opChanged();
    }
}
int PostObject::parent() const {
    return mParent;
}

void PostObject::setParent(int value) {
    if (mParent != value) {
        mParent = value;
        emit parentChanged();
    }
}
bool PostObject::sticky() const {
    return mSticky;
}

void PostObject::setSticky(bool value) {
    if (mSticky != value) {
        mSticky = value;
        emit stickyChanged();
    }
}
QString PostObject::subject() const {
    return mSubject;
}

void PostObject::setSubject(const QString &value) {
    if (mSubject != value) {
        mSubject = value;
        emit subjectChanged();
    }
}
QDateTime PostObject::timestamp() const {
    return mTimestamp;
}

void PostObject::setTimestamp(QDateTime value) {
    if (mTimestamp != value) {
        mTimestamp = value;
        emit timestampChanged();
    }
}
QString PostObject::trip() const {
    return mTrip;
}

void PostObject::setTrip(const QString &value) {
    if (mTrip != value) {
        mTrip = value;
        emit tripChanged();
    }
}
QString PostObject::tripType() const {
    return mTripType;
}

void PostObject::setTripType(const QString &value) {
    if (mTripType != value) {
        mTripType = value;
        emit tripTypeChanged();
    }
}
