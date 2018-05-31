#include "client.h"
#include <QTextStream>

Client::Client(QObject* parent) : QObject(parent) {
    rpc = new MaiaXmlRpcClient(QUrl("https://neos-server.org:3333"), this);

    QSslConfiguration config = rpc->sslConfiguration();
    config.setProtocol(QSsl::AnyProtocol);
    rpc->setSslConfiguration(config);

    connect(rpc, SIGNAL(sslErrors(QNetworkReply *, const QList<QSslError> &)),
            this, SLOT(handleSslErrors(QNetworkReply *, const QList<QSslError> &)));
}

void Client::ping() {
    QVariantList args;
    rpc->call("ping", args,
                this, SLOT(toString(QVariant &)),
                this, SLOT(testFault(int, const QString &)));
}

void Client::printQueue() {
    QVariantList args;
    rpc->call("printQueue", args,
                this, SLOT(toString(QVariant &)),
                this, SLOT(testFault(int, const QString &)));
}

void Client::solversAvailable() {
    QVariantList args;
    rpc->call("listAllSolvers", args,
                this, SLOT(toList(QVariant &)),
                this, SLOT(testFault(int, const QString &)));
}

void Client::solversAvailableinCategory() {
    QVariantList args;
    args << "milp";
    rpc->call("listSolversInCategory", args,
                this, SLOT(toList(QVariant &)),
                this, SLOT(testFault(int, const QString &)));
}

void Client::GetSolverTemplate() {
    QVariantList args;
    args << "milp" << "CPLEX" << "LP";
    rpc->call("getSolverTemplate", args,
                this, SLOT(toStringFile(QVariant &)),
                this, SLOT(testFault(int, const QString &)));
}

void Client::SubmitJob(const QString& email, const QString& solver, const QString& task) {
    QVariantList args;
    QFile f("../main/xmljob.txt");
    QTextStream in(&f);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug() << "Doesn't work\n";
           return;
    }
    QString a = in.readAll();
    int indexofemail = a.indexOf("</email>");
    a.insert(indexofemail, email);
    int indexofsolver = a.indexOf("</solver>");
    a.insert(indexofsolver, solver);
    int indexoftask = a.indexOf("]]></LP>");
    a.insert(indexoftask, task);
    args << a;
    QString number, password;
    rpc->call("submitJob", args,
                this, SLOT(toListFile(QVariant &)),
                this, SLOT(testFault(int, const QString &)));
}

void Client::JobInfo() {
    QVariantList args;
    QFile f("../main/jobinfo.txt");
    QTextStream in(&f);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug() << "Doesn't work\n";
           return;
    }
    QString a = in.readLine();
    QString b = in.readLine();
    qDebug() << a << " " << b << "\n";
    int c = a.toInt();
    args << c << b;
    rpc->call("getJobStatus", args,
                this, SLOT(toString(QVariant &)),
                this, SLOT(testFault(int, const QString &)));
}

void Client::toString(QVariant &arg) {
        qDebug() << arg.toString();
}

void Client::toStringFile(QVariant &arg) {
        QFile info("../main/SolverTemplate.txt");
        QTextStream out(&info);
        if (!info.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Doesn't work\n";
            return;
        }
        out << arg.toString();
}

void Client::toList(QVariant &arg) {
        QList<QVariant> a = arg.value<QList<QVariant>>();
        for (int i = 0; i < a.size(); ++i) {
          qDebug() << a[i].toString() << "\n";
        };
}

void Client::toListFile(QVariant &arg) {
        QList<QVariant> a = arg.value<QList<QVariant>>();
        QFile info("../main/jobinfo.txt");
        if (!info.open(QIODevice::WriteOnly | QIODevice::Text)) {
                qDebug() << "Don't\n";
                return;
        }
        for (int i = 0; i < a.size(); ++i) {
          qDebug() << a[i].toString() << "\n";
        };
}

void Client::testFault(int error, const QString &message) {
        qDebug() << "EEE:" << error << "-" << message;
}

void Client::handleSslErrors(QNetworkReply *reply, const QList<QSslError> &errors) {
    qDebug() << "SSL Error:" << errors;
    reply->ignoreSslErrors();
}
