#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <QQuickWindow>

#include "MainApp.h"
#include "Attachment.h"
#include "ThreadsView.h"
#include "PostsView.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<BoardModel>("MyLib", 1, 0,"BoardModel");
    qmlRegisterType<ThreadModel>("MyLib", 1, 0,"ThreadModel");
    qmlRegisterType<Attachment>("MyLib", 1, 0,"Attachment");
    qmlRegisterType<ThreadsView>("MyLib", 1, 0,"ThreadsView");
    qmlRegisterType<PostsView>("MyLib", 1, 0,"PostsView");

    QCoreApplication::setOrganizationName(QLatin1String("HikkaSoft"));
    QCoreApplication::setApplicationName(QLatin1String("Sosach"));
    QCoreApplication::setApplicationVersion("0.0.1");
    QGuiApplication app(argc, argv);

    QQmlEngine engine;
    QUrl url = QUrl::fromLocalFile(QStringLiteral("/home/wolph/workspace/harkach/qml/main.qml"));
    QQmlComponent rootComponent(&engine, url);

    if (rootComponent.isError()) {
        qFatal("%s", qPrintable(rootComponent.errorString()));
    }

    QQuickWindow *mainWindow = qobject_cast<QQuickWindow*>(rootComponent.beginCreate(engine.rootContext()));
    mainWindow->setIcon(QIcon(":/dvlogo.png"));

    MainApp *mainApp = new MainApp(mainWindow);
    engine.rootContext()->setContextObject(mainApp);

    rootComponent.completeCreate();
    return app.exec();
}
