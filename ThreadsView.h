#ifndef THREADSVIEW_H
#define THREADSVIEW_H

#include <QQuickItem>
#include <QDebug>
#include <QNetworkAccessManager>
#include "ThreadModel.h"
#include "ThreadObject.h"

class ThreadsView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString board READ board WRITE setBoard NOTIFY boardChanged)
    Q_PROPERTY(bool downloading READ downloading WRITE setDownloading NOTIFY downloadingChanged)
    Q_PROPERTY(ThreadModel* threadModel READ getThreadModel CONSTANT)

public:
    ThreadsView(QQuickItem *parent = nullptr);
    ThreadModel *getThreadModel() const noexcept;

    QString board() const;
    void setBoard(const QString &board);

    bool downloading() const;
    void setDownloading(bool downloading);

private:
    QString mBoard;
    bool mDownloading;

    void requestThreads(const QString &board);
    void processThreads();

    QNetworkAccessManager manager;
    ThreadModel mThreadModel;


signals:
    void boardChanged();
    void downloadingChanged();

public slots:
};

#endif // THREADSVIEW_H
