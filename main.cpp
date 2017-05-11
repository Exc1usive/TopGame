#include "BombermanWidget.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>

#define LOGINFILE false

#if LOGINFILE == true
QScopedPointer<QFile>   m_logFile;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if LOGINFILE == true
    m_logFile.reset(new QFile(QApplication::applicationDirPath() + "/log/log" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + ".txt"));
    m_logFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);
#endif

    qDebug(logDebug()) << "Game start";



    BombermanWidget w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}

#if LOGINFILE == true
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream out(m_logFile.data());
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    switch (type)
    {
    case QtInfoMsg:     out << "INFO        "; break;
    case QtDebugMsg:    out << "DEBUG       "; break;
    case QtWarningMsg:  out << "WARNING     "; break;
    case QtCriticalMsg: out << "CRITICAL    "; break;
    case QtFatalMsg:    out << "FATAL       "; break;
    }
    out << context.category << ": " << msg << endl;
    out.flush();
}
#endif
