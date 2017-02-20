#ifndef POSTSVIEW_H
#define POSTSVIEW_H

#include <QQuickItem>
#include <QUrlQuery>
#include <QDebug>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "PostModel.h"
#include "PostObject.h"
#include <algorithm>

#include <QGuiApplication>
#include <QQuickWindow>
#include <QQuickView>

struct ThreadNum
{
private:
    Q_GADGET
    Q_PROPERTY(QString board MEMBER board CONSTANT)
    Q_PROPERTY(int thread MEMBER thread CONSTANT)
    Q_PROPERTY(QString subj MEMBER subj CONSTANT)

public:

    inline bool operator==(const ThreadNum &a) {
        return (a.thread==thread && a.board== board && a.subj == subj);
    }

    QString board;
    int thread;
    QString subj;
};
Q_DECLARE_METATYPE(ThreadNum)

class PostsView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(ThreadNum threadNum READ threadNum WRITE setThreadNum NOTIFY threadNumChanged)
    Q_PROPERTY(bool downloading READ downloading WRITE setDownloading NOTIFY downloadingChanged)
    Q_PROPERTY(PostModel* postModel READ getPostModel CONSTANT)

public:
    PostsView(QQuickItem *parent = nullptr);
    PostModel *getPostModel() const noexcept;

    ThreadNum threadNum() const noexcept;
    void setThreadNum(ThreadNum value);

    bool downloading() const noexcept;
    void setDownloading(bool downloading);

private:
    void requestPostsByAbsNum(const QString &board, int thread, int num);
    void processPosts();

    PostModel mPostModel;
    QNetworkAccessManager manager;

    ThreadNum mThreadNum;
    bool mDownloading;

signals:
    void downloadingChanged();
    void threadNumChanged();

public slots:
    void updatePage();

};

#endif // POSTSVIEW_H
