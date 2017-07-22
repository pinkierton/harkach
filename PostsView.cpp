#include "PostsView.h"



PostsView::PostsView(QQuickItem *parent) : QQuickItem(parent)
{

}

PostModel *PostsView::getPostModel() const noexcept {
    return const_cast<PostModel* const>(&mPostModel);
}

void PostsView::requestPostsByAbsNum(const QString &board, int thread, int num) {
    setDownloading(true);
    //mPostModel.resetPosts();

    QUrlQuery urlQuery;
    urlQuery.addQueryItem(QLatin1String("task"), QLatin1String("get_thread"));
    urlQuery.addQueryItem(QLatin1String("board"), board);
    urlQuery.addQueryItem(QLatin1String("thread"), QString::number(thread));
    urlQuery.addQueryItem(QLatin1String("num"), QString::number(num));

    QUrl url(QLatin1String("https://2ch.hk/makaba/mobile.fcgi"));
    url.setQuery(urlQuery);

    qDebug() << url;
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

    connect(reply, &QNetworkReply::finished, this, &PostsView::processPosts);
}

void PostsView::processPosts() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QNetworkReply::NetworkError error = reply->error();
    if (error) {
        qWarning() << Q_FUNC_INFO << error << reply->readAll();
    } else {
        QByteArray data = reply->readAll();
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

        if (parseError.error) {
            qWarning() << parseError.error << parseError.errorString();
        } else if (! doc.isArray()) { // API вернул ошибку
            qDebug() << "[WW] API error: "  << doc;
            // Здесь можно вызвать обработчик
        } else {
            QList<PostObject*> posts;
            posts.reserve(600);

            QJsonArray postArr = doc.array();

            for (const QJsonValue &postRef : qAsConst(postArr)) {
                QJsonObject post = postRef.toObject();

                posts << new PostObject(post);
            }

            mPostModel.setPosts(std::move(posts));
        }
    }

    reply->deleteLater();
    setDownloading(false);
}

void PostsView::updatePage() {
    qDebug() << Q_FUNC_INFO
             << mPostModel.getPosts().first()->num()
             << mPostModel.getPosts().last()->num();


    requestPostsByAbsNum(mThreadNum.board, mThreadNum.thread, mPostModel.getPosts().last()->num() + 1);
    // Пост #.last()->num() уже есть, нужен следующий
}

ThreadNum PostsView::threadNum() const noexcept{
    return mThreadNum;
}

void PostsView::setThreadNum(ThreadNum value) {
    if (!(mThreadNum == value)) {
        requestPostsByAbsNum(value.board, value.thread, value.thread);
        mThreadNum = value;
        emit threadNumChanged();
    }
}

bool PostsView::downloading() const noexcept{
    return mDownloading;
}

void PostsView::setDownloading(bool downloading) {
    if (mDownloading != downloading) {
        mDownloading = downloading;
        emit downloadingChanged();
    }
}
