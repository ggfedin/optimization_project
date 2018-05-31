#include <QtCore>
#include <QDebug>
#include <iostream>

#include "client.h"

int main(int argc, char* argv[]) {
    QCoreApplication app( argc, argv );
    Client NEOS;
    const QString email = "dakhalikov@edu.hse.ru";
    const QString solver = "CPLEX";
    const QString task = "";
    //NEOS.printQueue();
    //NEOS.solversAvailable();
    //NEOS.solversAvailableinCategory();
    //NEOS.GetSolverTemplate();
    NEOS.SubmitJob(email, solver, task);
    NEOS.ping();
    //NEOS.JobInfo();
    app.exec();
}
