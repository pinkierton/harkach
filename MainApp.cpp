#include "MainApp.h"
#include <QDebug>
#include <QHttpMultiPart>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QStringBuilder>
#include <QDateTime>
#include <QFile>

#include "Board.h"
#include <QEventLoop>
#include <QQmlListProperty>

const QUrl MainApp::postUrl(QStringLiteral("https://2ch.hk/user/posting?nc=1"));
const QUrl MainApp::getBoardsUrl(QStringLiteral("https://2ch.hk/makaba/mobile.fcgi?task=get_boards"));

MainApp::MainApp(QObject *parent): QObject(parent)
{
    QSettings settings;
    int size = settings.beginReadArray("boards");
    if (size > 0) {
        QList<Board*> boards;
        boards.reserve(size);
        for (int i = 0; i < size; ++i) {
            settings.setArrayIndex(i);
            QString id = settings.value(QLatin1String("id")).toString();
            QString name = settings.value(QLatin1String("name")).toString();
            QString category = settings.value(QLatin1String("category")).toString();
            QString defaultName = settings.value(QLatin1String("defaultName")).toString();
            int bumpLimit = settings.value(QLatin1String("bumpLimit")).toInt();
            int pages = settings.value(QLatin1String("pages")).toInt();
            bool enableLikes = settings.value(QLatin1String("enableLikes")).toBool();
            bool enablePosting = settings.value(QLatin1String("enablePosting")).toBool();
            bool enableThreadTags = settings.value(QLatin1String("enableThreadTags")).toBool();
            bool sage = settings.value(QLatin1String("sage")).toBool();
            bool tripcodes = settings.value(QLatin1String("tripcodes")).toBool();

            Board *board = new Board(id, name, category, defaultName, bumpLimit, pages, enableLikes, enablePosting, enableThreadTags, sage, tripcodes);
            boards << board;
        }

        mBoardModel.setBoards(std::move(boards));
    }
    else {
        requestBoards();
    }
    settings.endArray();
}

BoardModel *MainApp::getBoardModel() const {
    return const_cast<BoardModel* const>(&mBoardModel);
}

void MainApp::requestBoards() {
    QNetworkRequest request(getBoardsUrl);
    QNetworkReply *reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, this, &MainApp::processBoards);
}

void MainApp::processBoards() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    auto error = reply->error();

    if (error) {
        qDebug() << Q_FUNC_INFO << error;
    } else {
        QByteArray data = reply->readAll();

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
        if (parseError.error) {
            qWarning() << parseError.error << parseError.errorString();
        } else {
            QList<Board*> boards;
            boards.reserve(256);

            auto obj = doc.object();

            for (QJsonObject::Iterator iterCat = obj.begin(); iterCat!=obj.end(); ++iterCat) {
                QJsonArray boardArr = iterCat.value().toArray();

                for (QJsonArray::Iterator iterBoard = boardArr.begin(); iterBoard!=boardArr.end(); ++iterBoard) {
                    QJsonObject boardObj = iterBoard->toObject();
                    boards << new Board(boardObj, &mBoardModel);
                }
            }

            QSettings settings;
            settings.beginWriteArray("boards");

            int i = 0;
            for (Board* board : qAsConst(boards)) {
                settings.setArrayIndex(i++);
                settings.setValue(QLatin1String("id"), board->id());
                settings.setValue(QLatin1String("name"), board->name());
                settings.setValue(QLatin1String("category"), board->category());
                settings.setValue(QLatin1String("defaultName"), board->defaultName());
                settings.setValue(QLatin1String("bumpLimit"), board->bumpLimit());
                settings.setValue(QLatin1String("pages"), board->pages());
                settings.setValue(QLatin1String("enableLikes"), board->enableLikes());
                settings.setValue(QLatin1String("enablePosting"), board->enablePosting());
                settings.setValue(QLatin1String("enableThreadTags"), board->enableThreadTags());
                settings.setValue(QLatin1String("sage"), board->sage());
                settings.setValue(QLatin1String("tripcodes"), board->tripcodes());
            }
            settings.endArray();

            mBoardModel.setBoards(std::move(boards));
        }
    }

    reply->deleteLater();
}





void MainApp::sendPost(const QString &board, const QString &thread, const QString &post, const QString &id, const QString &captcha) {

    //qDebug() << Q_FUNC_INFO << board << thread << post << id << captcha;

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart taskPart;
    taskPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"task\""));
    taskPart.setBody("post");

    QHttpPart boardPart;
    boardPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"board\""));
    boardPart.setBody(board.toUtf8());

    QHttpPart threadPart;
    threadPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"thread\""));
    threadPart.setBody(thread.toUtf8());

    QHttpPart commentPart;
    commentPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"comment\""));
    commentPart.setBody(post.toUtf8());

    QHttpPart captchaTypePart;
    captchaTypePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"captcha_type\""));
    captchaTypePart.setBody("emoji_captcha");

    multiPart->append(taskPart);
    multiPart->append(boardPart);
    multiPart->append(threadPart);
    multiPart->append(commentPart);

    multiPart->append(captchaTypePart);

    QNetworkRequest request(postUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("multipart/form-data; boundary=").append(multiPart->boundary()));
    //request.setHeader(QNetworkRequest::UserAgentHeader, "Abuloh/5.0 (windows; DOS x86_64) AppleWebKit/538.1 (KHTML, like Gecko) abupidor/0.0.1 abupidor/538.1");

    QNetworkReply *reply = manager.post(request, multiPart);
    multiPart->setParent(reply);

    connect(reply, &QNetworkReply::finished, [reply](){
        auto error = reply->error();

        if (error) {
            qDebug() << error;
        } else {
            QByteArray data = reply->readAll();
            QString stringData(data);
            qDebug() << stringData;
        }

        reply->deleteLater();
    });
}

ThreadNum MainApp::makeThreadNum(const QString &board, int thread, const QString &subj) const noexcept {
    return ThreadNum{board, thread, subj};
}
