#include "Board.h"
#include <QDebug>

Board::Board(const QString &id,
             const QString &name,
             const QString &category,
             const QString &defaultName,
             int bumpLimit,
             int pages,
             bool enableLikes,
             bool enablePosting,
             bool enableThreadTags,
             bool sage,
             bool tripcodes,
             QObject *parent)
    :
      QObject(parent),
      mId(id),
      mName(name),
      mCategory(category),
      mDefaultName(defaultName),
      mBumpLimit(bumpLimit),
      mPages(pages),
      mEnableLikes(enableLikes),
      mEnablePosting(enablePosting),
      mEnableThreadTags(enableThreadTags),
      mSage(sage),
      mTripcodes(tripcodes)
{
}

Board::Board(const QJsonObject &boardObj, QObject *parent) :
    QObject (parent),
    mId(boardObj.value(QStringLiteral("id")).toString()),
    mName(boardObj.value(QStringLiteral("name")).toString()),
    mCategory(boardObj.value(QStringLiteral("category")).toString()),
    mDefaultName(boardObj.value(QStringLiteral("default_name")).toString()),
    mBumpLimit(boardObj.value(QStringLiteral("bump_limit")).toInt()),
    mPages(boardObj.value(QStringLiteral("pages")).toInt()),
    mEnableLikes(static_cast<bool>(boardObj.value(QStringLiteral("enable_likes")).toInt())),
    mEnablePosting(static_cast<bool>(boardObj.value(QStringLiteral("enable_posting")).toInt())),
    mEnableThreadTags(static_cast<bool>(boardObj.value(QStringLiteral("enable_thread_tags")).toInt())),
    mSage(static_cast<bool>(boardObj.value(QStringLiteral("sage")).toInt())),
    mTripcodes(static_cast<bool>(boardObj.value(QStringLiteral("tripcodes")).toInt()))
{
//    if (mId == QLatin1String("d")) {
//        qDebug() << "id              " << id();
//        qDebug() << "name            " << name();
//        qDebug() << "category        " << category();
//        qDebug() << "defaultName     " << defaultName();
//        qDebug() << "bumpLimit       " << bumpLimit();
//        qDebug() << "pages           " << pages();
//        qDebug() << "enableLikes     " << enableLikes();
//        qDebug() << "enablePosting   " << enablePosting();
//        qDebug() << "enableThreadTags" << enableThreadTags();
//        qDebug() << "sage            " << sage();
//        qDebug() << "tripcodes       " << tripcodes();
//    }
}

QString Board::id() const {
    return mId;
}

void Board::setId(const QString &val) {
    if (mId != val) {
        mId = val;
        emit idChanged();
    }
}

QString Board::name() const {
    return mName;
}

void Board::setName(const QString &val) {
    if (mName != val) {
        mName = val;
        emit nameChanged();
    }
}

QString Board::category() const {
    return mCategory;
}

void Board::setCategory(const QString &val) {
    if (mCategory != val) {
        mCategory = val;
        emit categoryChanged();
    }
}

QString Board::defaultName() const {
    return mDefaultName;
}

void Board::setDefaultName(const QString &val) {
    if (mDefaultName != val) {
        mDefaultName = val;
        emit defaultNameChanged();
    }
}

int Board::bumpLimit() const {
    return mBumpLimit;
}

void Board::setBumpLimit(int val) {
    if (mBumpLimit != val) {
        mBumpLimit = val;
        emit bumpLimitChanged();
    }
}

int Board::pages() const {
    return mPages;
}

void Board::setPages(int val) {
    if (mPages != val) {
        mPages = val;
        emit pagesChanged();
    }
}

bool Board::enableLikes() const {
    return mEnableLikes;
}

void Board::setEnableLikes(bool val) {
    if (mEnableLikes != val) {
        mEnableLikes = val;
        emit enableLikesChanged();
    }
}

bool Board::enablePosting() const {
    return mEnablePosting;
}

void Board::setEnablePosting(bool val) {
    if (mEnablePosting != val) {
        mEnablePosting = val;
        emit enablePostingChanged();
    }
}

bool Board::enableThreadTags() const {
    return mEnableThreadTags;
}

void Board::setEnableThreadTags(bool val) {
    if (mEnableThreadTags != val) {
        mEnableThreadTags = val;
        emit enableThreadTagsChanged();
    }
}

bool Board::sage() const {
    return mSage;
}

void Board::setSage(bool val) {
    if (mSage != val) {
        mSage = val;
        emit sageChanged();
    }
}

bool Board::tripcodes() const {
    return mTripcodes;
}

void Board::setTripcodes(bool val) {
    if (mTripcodes != val) {
        mTripcodes = val;
        emit tripcodesChanged();
    }
}
