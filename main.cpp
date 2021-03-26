#include <QtCore/QCoreApplication>
#include <iostream>

#include "OperationCreator.h"

#include "Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;



    return a.exec();
}
