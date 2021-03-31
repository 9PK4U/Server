#include <QtCore/QCoreApplication>
#include <qobject.h>



#include "Server/Server.h"
#include "Game/Game.h"
#include "Application/Application.h"

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);

	Server server;

	Application app(server.getController());
    return a.exec();
}
