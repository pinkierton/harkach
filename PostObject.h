#ifndef POSTOBJECT_H
#define POSTOBJECT_H

#include <QDateTime>
#include <QObject>
#include <QJsonObject>
#include <QVariant>
#include "Attachment.h"

class PostObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(        bool banned     READ banned     WRITE setBanned     NOTIFY bannedChanged    )
    Q_PROPERTY(        bool closed     READ closed     WRITE setClosed     NOTIFY closedChanged    )
    Q_PROPERTY(     QString comment    READ comment    WRITE setComment    NOTIFY commentChanged   )
    Q_PROPERTY(     QString date       READ date       WRITE setDate       NOTIFY dateChanged      )
    Q_PROPERTY(     QString email      READ email      WRITE setEmail      NOTIFY emailChanged     )
    Q_PROPERTY( QObjectList files      READ files      WRITE setFiles      NOTIFY filesChanged     )
    Q_PROPERTY(   QDateTime lasthit    READ lasthit    WRITE setLasthit    NOTIFY lasthitChanged   )
    Q_PROPERTY(     QString name       READ name       WRITE setName       NOTIFY nameChanged      )
    Q_PROPERTY(         int num        READ num        WRITE setNum        NOTIFY numChanged       )
    Q_PROPERTY(        bool op         READ op         WRITE setOp         NOTIFY opChanged        )
    Q_PROPERTY(         int parent     READ parent     WRITE setParent     NOTIFY parentChanged    )
    Q_PROPERTY(        bool sticky     READ sticky     WRITE setSticky     NOTIFY stickyChanged    )
    Q_PROPERTY(     QString subject    READ subject    WRITE setSubject    NOTIFY subjectChanged   )
    Q_PROPERTY(   QDateTime timestamp  READ timestamp  WRITE setTimestamp  NOTIFY timestampChanged )
    Q_PROPERTY(     QString trip       READ trip       WRITE setTrip       NOTIFY tripChanged      )
    Q_PROPERTY(     QString tripType   READ tripType   WRITE setTripType   NOTIFY tripTypeChanged  )

public:
    explicit PostObject(QObject *parent = nullptr);
    explicit PostObject(const QJsonObject &postObj, QObject *parent = nullptr);

    bool banned() const;
    void setBanned(bool value);

    bool closed() const;
    void setClosed(bool value);

    QString comment() const;
    void setComment(const QString &value);

    QString date() const;
    void setDate(const QString &value);

    QString email() const;
    void setEmail(const QString &value);

    QObjectList files() const;
    void setFiles(QObjectList value);

    QDateTime lasthit() const;
    void setLasthit(QDateTime value);

    QString name() const;
    void setName(const QString &value);

    int num() const;
    void setNum(int value);

    bool op() const;
    void setOp(bool value);

    int parent() const;
    void setParent(int value);

    bool sticky() const;
    void setSticky(bool value);

    QString subject() const;
    void setSubject(const QString &value);

    QDateTime timestamp() const;
    void setTimestamp(QDateTime value);

    QString trip() const;
    void setTrip(const QString &value);

    QString tripType() const;
    void setTripType(const QString &value);

private:
    bool mBanned;
    bool mClosed;
    QString mComment;
    QString mDate;
    QString mEmail;
    QObjectList mFiles;
    QDateTime mLasthit;
    QString mName;
    int mNum;
    bool mOp;
    int mParent;
    bool mSticky;
    QString mSubject;
    QDateTime mTimestamp;
    QString mTrip;
    QString mTripType;

signals:
    void bannedChanged();
    void closedChanged();
    void commentChanged();
    void dateChanged();
    void emailChanged();
    void filesChanged();
    void lasthitChanged();
    void nameChanged();
    void numChanged();
    void opChanged();
    void parentChanged();
    void stickyChanged();
    void subjectChanged();
    void timestampChanged();
    void tripChanged();
    void tripTypeChanged();

public slots:
};

#endif // POSTOBJECT_H
