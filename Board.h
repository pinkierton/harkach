#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QJsonObject>

class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString id               READ id               WRITE setId               NOTIFY idChanged               )
    Q_PROPERTY( QString name             READ name             WRITE setName             NOTIFY nameChanged             )
    Q_PROPERTY( QString category         READ category         WRITE setCategory         NOTIFY categoryChanged         )
    Q_PROPERTY( QString defaultName      READ defaultName      WRITE setDefaultName      NOTIFY defaultNameChanged      )
    Q_PROPERTY( int     bumpLimit        READ bumpLimit        WRITE setBumpLimit        NOTIFY bumpLimitChanged        )
    Q_PROPERTY( int     pages            READ pages            WRITE setPages            NOTIFY pagesChanged            )
    Q_PROPERTY( bool    enableLikes      READ enableLikes      WRITE setEnableLikes      NOTIFY enableLikesChanged      )
    Q_PROPERTY( bool    enablePosting    READ enablePosting    WRITE setEnablePosting    NOTIFY enablePostingChanged    )
    Q_PROPERTY( bool    enableThreadTags READ enableThreadTags WRITE setEnableThreadTags NOTIFY enableThreadTagsChanged )
    Q_PROPERTY( bool    sage             READ sage             WRITE setSage             NOTIFY sageChanged             )
    Q_PROPERTY( bool    tripcodes        READ tripcodes        WRITE setTripcodes        NOTIFY tripcodesChanged        )

public:
    explicit Board(const QString &id, const QString &name, const QString &category, const QString &defaultName, int bumpLimit, int pages, bool enableLikes, bool enablePosting, bool enableThreadTags, bool sage, bool tripcodes, QObject *parent = nullptr);

    explicit Board(const QJsonObject &boardObj, QObject *parent = nullptr);

    QString id() const;
    void setId(const QString &val);

    QString name() const;
    void setName(const QString &val);

    QString category() const;
    void setCategory(const QString &val);

    QString defaultName() const;
    void setDefaultName(const QString &val);

    int bumpLimit() const;
    void setBumpLimit(int val);

    int pages() const;
    void setPages(int val);

    bool enableLikes() const;
    void setEnableLikes(bool val);

    bool enablePosting() const;
    void setEnablePosting(bool val);

    bool enableThreadTags() const;
    void setEnableThreadTags(bool val);

    bool sage() const;
    void setSage(bool val);

    bool tripcodes() const;
    void setTripcodes(bool val);

private:
    QString mId;
    QString mName;
    QString mCategory;
    QString mDefaultName;
    int     mBumpLimit;
    int     mPages;
    bool    mEnableLikes;
    bool    mEnablePosting;
    bool    mEnableThreadTags;
    bool    mSage;
    bool    mTripcodes;

signals:
    void idChanged();
    void nameChanged();
    void categoryChanged();
    void defaultNameChanged();
    void bumpLimitChanged();
    void pagesChanged();
    void enableLikesChanged();
    void enablePostingChanged();
    void enableThreadTagsChanged();
    void sageChanged();
    void tripcodesChanged();

public slots:
};

#endif // BOARD_H
