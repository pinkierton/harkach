#ifndef MAINAPP_H
#define MAINAPP_H

#include <QObject>

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSettings>

#include "BoardModel.h"
#include "Attachment.h"
#include "PostsView.h"

#define PROJECT_ROOT "/home/wolph/workspace/harkach/"

class MainApp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BoardModel* boardModel READ getBoardModel CONSTANT)

public:
    explicit MainApp(QObject *parent = nullptr);
    BoardModel *getBoardModel() const;

private:
    static const QUrl postUrl;
    static const QUrl getBoardsUrl;

    QNetworkAccessManager manager;
    BoardModel mBoardModel;

    void requestBoards();
    void processBoards();

public slots:
    void sendPost(const QString &board, const QString &thread, const QString &post, const QString &id, const QString &captcha);
    ThreadNum makeThreadNum(const QString &board, int thread, const QString &subj) const noexcept;

private slots:
};

#endif // MAINAPP_H
