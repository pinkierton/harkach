#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QObjectList>

class Attachment : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString name             READ name             WRITE setName             NOTIFY nameChanged            )
    Q_PROPERTY( QString path             READ path             WRITE setPath             NOTIFY pathChanged            )
    Q_PROPERTY( QString thumbnail        READ thumbnail        WRITE setThumbnail        NOTIFY thumbnailChanged       )
    Q_PROPERTY( QString md5              READ md5              WRITE setMd5              NOTIFY md5Changed             )
    Q_PROPERTY(     int type             READ type             WRITE setType             NOTIFY typeChanged            )
    Q_PROPERTY(     int size             READ size             WRITE setSize             NOTIFY sizeChanged            )
    //FIXME
    Q_PROPERTY(     int imageWidth       READ width            WRITE setWidth            NOTIFY widthChanged           )
    Q_PROPERTY(     int imageHeight      READ height           WRITE setHeight           NOTIFY heightChanged          )
    Q_PROPERTY(     int thumbnailWidth   READ thumbnailWidth   WRITE setThumbnailWidth   NOTIFY thumbnailWidthChanged  )
    Q_PROPERTY(     int thumbnailHeight  READ thumbnailHeight  WRITE setThumbnailHeight  NOTIFY thumbnailHeightChanged )

public:
    explicit Attachment(QObject *parent = 0);
    explicit Attachment(const QJsonObject &obj, QObject *parent = 0);

    static QList<Attachment*> makeAttachmentList(const QJsonArray &attachArr, QObject *parent = nullptr);

    static QObjectList makeObjectList(const QJsonArray &attachArr, QObject *parent = nullptr);

    void setName (const QString &value);
    QString name() const;

    void setPath (const QString &value);
    QString path() const;

    void setThumbnail (const QString &value);
    QString thumbnail() const;

    void setMd5 (const QString &value);
    QString md5() const;

    void setType (int value);
    int type() const;

    void setSize (int value);
    int size() const;

    void setWidth (int value);
    int width() const;

    void setHeight (int value);
    int height() const;

    void setThumbnailWidth (int value);
    int thumbnailWidth() const;

    void setThumbnailHeight (int value);
    int thumbnailHeight() const;

private:
    QString mName;
    QString mPath;
    QString mThumbnail;
    QString mMd5;
    int mType;
    int mSize;
    int mWidth;
    int mHeight;
    int mThumbnailWidth;
    int mThumbnailHeight;

signals:
    void nameChanged();
    void pathChanged();
    void thumbnailChanged();
    void md5Changed();
    void typeChanged();
    void sizeChanged();
    void widthChanged();
    void heightChanged();
    void thumbnailWidthChanged();
    void thumbnailHeightChanged();

public slots:
};

typedef QList<Attachment*> AttachmentList;

#endif // ATTACHMENT_H
