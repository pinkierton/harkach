#include "Attachment.h"
#include "ThreadsView.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QStringBuilder>

ThreadsView::ThreadsView(QQuickItem *parent) : QQuickItem(parent), mDownloading(false)
{

}

ThreadModel *ThreadsView::getThreadModel() const noexcept {
    return const_cast<ThreadModel* const>(&mThreadModel);
}

QString ThreadsView::board() const
{
    return mBoard;
}

void ThreadsView::setBoard(const QString &board)
{
    if (mBoard != board) {
        mBoard = board;
        requestThreads(board);
        emit boardChanged();
    }
}

bool ThreadsView::downloading() const
{
    return mDownloading;
}

void ThreadsView::setDownloading(bool downloading)
{
    if (mDownloading != downloading) {
        mDownloading = downloading;
        emit downloadingChanged();
    }
}

void ThreadsView::requestThreads(const QString &board) {
    setDownloading(true);
    mThreadModel.resetThreads();


    const QUrl getThreadsUrl(QStringLiteral("https://2ch.hk/") % board % QStringLiteral("/catalog.json"));
    //const QUrl getThreadsUrl(QStringLiteral("https://2ch.hk/") % board % QStringLiteral("/threads.json"));

    QNetworkRequest request(getThreadsUrl);
    QNetworkReply *reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, this, &ThreadsView::processThreads);
}

void ThreadsView::processThreads() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    auto error = reply->error();
    if (error) {
        qWarning() << Q_FUNC_INFO << error;
    } else {
        QByteArray data = reply->readAll();
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

        if (parseError.error) {
            qWarning() << parseError.error << parseError.errorString();
        } else {
            QList<ThreadObject*> threads;
            threads.reserve(256);

            QJsonArray threadArr = doc.object()[QLatin1String("threads")].toArray();

            for (const QJsonValue &threadRef : qAsConst(threadArr)) {
                threads << new ThreadObject(threadRef.toObject());
            }
            mThreadModel.setThreads(std::move(threads));
        }
    }
    reply->deleteLater();
    setDownloading(false);
}
