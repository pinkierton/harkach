#include "Attachment.h"
#include <QDebug>

Attachment::Attachment(QObject *parent) : QObject(parent)
{

}

Attachment::Attachment(const QJsonObject &obj, QObject *parent)
    : QObject(parent),
      mName(obj[QLatin1String("name")].toString()),
      mPath(obj[QLatin1String("path")].toString()),
      mThumbnail(obj[QLatin1String("thumbnail")].toString()),
      mMd5(obj[QLatin1String("md5")].toString()),
      mType(obj[QLatin1String("type")].toInt()),
      mSize(obj[QLatin1String("size")].toInt()),
      mWidth(obj[QLatin1String("width")].toInt()),
      mHeight(obj[QLatin1String("height")].toInt()),
      mThumbnailWidth(obj[QLatin1String("tn_width")].toInt()),
      mThumbnailHeight(obj[QLatin1String("tn_height")].toInt())
{
}

QList<Attachment *> Attachment::makeAttachmentList(const QJsonArray &attachArr, QObject *parent)  {
    QList<Attachment*> result;
    result.reserve(8);
    for (const QJsonValue &attach : qAsConst(attachArr)) {
        result << new Attachment(attach.toObject(), parent);
    }
    return result;
}

QObjectList Attachment::makeObjectList(const QJsonArray &attachArr, QObject *parent)  {
    QObjectList result;
    result.reserve(8);
    for (const QJsonValue &attach : qAsConst(attachArr)) {
        result << new Attachment(attach.toObject(), parent);
    }
    return result;
}

void Attachment::setName (const QString &value) {
    if (mName != value) {
        mName = value;
        emit nameChanged();
    }
}

QString Attachment::name() const {
    return mName;
}

void Attachment::setPath (const QString &value) {
    if (mPath != value) {
        mPath = value;
        emit pathChanged();
    }
}

QString Attachment::path() const {
    return mPath;
}

void Attachment::setThumbnail (const QString &value) {
    if (mThumbnail != value) {
        mThumbnail = value;
        emit thumbnailChanged();
    }
}

QString Attachment::thumbnail() const {
    return mThumbnail;
}

void Attachment::setMd5 (const QString &value) {
    if (mMd5 != value) {
        mMd5 = value;
        emit md5Changed();
    }
}

QString Attachment::md5() const {
    return mMd5;
}

void Attachment::setType (int value) {
    if (mType != value) {
        mType = value;
        emit typeChanged();
    }
}

int Attachment::type() const {
    return mType;
}

void Attachment::setSize (int value) {
    if (mSize != value) {
        mSize = value;
        emit sizeChanged();
    }
}

int Attachment::size() const {
    return mSize;
}

void Attachment::setWidth (int value) {
    if (mWidth != value) {
        mWidth = value;
        emit widthChanged();
    }
}

int Attachment::width() const {
    return mWidth;
}

void Attachment::setHeight (int value) {
    if (mHeight != value) {
        mHeight = value;
        emit heightChanged();
    }
}

int Attachment::height() const {
    return mHeight;
}

void Attachment::setThumbnailWidth (int value) {
    if (mThumbnailWidth != value) {
        mThumbnailWidth = value;
        emit thumbnailWidthChanged();
    }
}

int Attachment::thumbnailWidth() const {
    return mThumbnailWidth;
}

void Attachment::setThumbnailHeight (int value) {
    if (mThumbnailHeight != value) {
        mThumbnailHeight = value;
        emit thumbnailHeightChanged();
    }
}

int Attachment::thumbnailHeight() const {
    return mThumbnailHeight;
}
