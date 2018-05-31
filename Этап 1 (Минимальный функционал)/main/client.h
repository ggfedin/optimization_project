#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include "maiaXmlRpcClient.h"

class Client : public QObject {
    Q_OBJECT

    public:
        Client(QObject* parent = 0);

    public slots:
        void ping();
        void printQueue();
        void solversAvailable();
        void solversAvailableinCategory();
        void GetSolverTemplate();
        void SubmitJob(const QString& email, const QString& solver, const QString& task);
        void JobInfo();

    private slots:
        void toList(QVariant &);
        void toListFile(QVariant &);
        void toString(QVariant &);
        void toStringFile(QVariant &);
        void testFault(int, const QString &);
        void handleSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

    private:
        MaiaXmlRpcClient *rpc;
};

#endif
