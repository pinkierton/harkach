#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <QQuickWindow>
#include <QCommandLineParser>

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

    QCommandLineParser parser;
    parser.setApplicationDescription("Десктопный клиент для имиджборд");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption usercodeOption(QStringList() << "c" << "usercode", "Кука пасскода", "code");
    parser.addOption(usercodeOption);

    parser.process(app);

    const QString usercode = parser.value(usercodeOption);

    QQmlEngine engine;
    QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent rootComponent(&engine, url);

    if (rootComponent.isError()) {
        qFatal("%s", qPrintable(rootComponent.errorString()));
    }

    QQuickWindow *mainWindow = qobject_cast<QQuickWindow*>(rootComponent.beginCreate(engine.rootContext()));
    mainWindow->setIcon(QIcon(":/dvlogo.png"));

    MainApp *mainApp = new MainApp(mainWindow);
    engine.rootContext()->setContextObject(mainApp);
    mainApp->setUsercode(usercode);

    rootComponent.completeCreate();
    return app.exec();
}
