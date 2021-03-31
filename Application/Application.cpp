#include "Application.h"
#include <QFile>

Application::Application(ServerController& controller) : controller(controller)
{
    findGameUsers       = new QMap<int, User*>();
    autorizationUsers   = new QMap<int, User*>();
    activeGames         = new QMap<int, Game*>();
    QObject::connect(&controller, &ServerController::newOperation, this, &Application::operationProcessor);
}

void Application::operationProcessor(int id, Operation operation)
{
    switch (operation.getType())
    {
    case Operation::Type::Autorization:
        autorization(id, operation.getParametrs());
        break;
    case Operation::Type::Registration:
        registration(id, operation.getParametrs());
        break;
    case Operation::Type::EnterCell:
        enterCell(id, operation.getParametrs());
        break;
    case Operation::Type::GetStatistic:
        qDebug() << "Not command";
        break;
    case Operation::Type::FindGame:
        findGame(id, operation.getParametrs());
        break;
    case Operation::Type::EndGame:
        qDebug() << "Not command";
        break;
    case Operation::Type::StatusGame:
        qDebug() << "Not command";
        break;
    case Operation::Type::Error:
        qDebug() << "Not command";
        break;
    default:
        break;
    }
}

void Application::autorization(int idClient, Parametrs parametrs)
{
    if (parametrs.find("Login") == parametrs.end()
        || parametrs.find("Password") == parametrs.end())
    {
        controller.response(idClient, OperationCreator::createErrorResponse("Incorrect parametrs"));
        return;
    }
    auto login = parametrs["Login"];
    auto password = parametrs["Password"];


    QFile file("User.txt");
    if (file.open(QIODevice::ReadOnly)) {

        while (!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(" ");
            std::string loginFile = lst.at(0).toUtf8().constData();//Login
            std::string passwordFile = lst.at(1).toUtf8().constData();//Password

            if (login == loginFile && (password == passwordFile || password + "\r\n" == passwordFile))
            {
                User* user = new User(login);
                (*autorizationUsers)[idClient] = new User(login);
                file.close();
                controller.response(idClient, OperationCreator::createAutorizationResponse(Process::Success));
                return;

            }
        }
        file.close();

    }
    else
    {
        qDebug() << "Error FILE";
    }
    controller.response(idClient, OperationCreator::createAutorizationResponse(Process::Failed));
}

void Application::registration(int idClient, Parametrs parametrs)
{
    if (parametrs.find("Login") == parametrs.end()
        || parametrs.find("Password") == parametrs.end())
    {
        controller.response(idClient, OperationCreator::createErrorResponse("Incorrect parametrs"));
        return;
    }

    auto login = parametrs["Login"];
    auto password = parametrs["Password"];

    string finishStr;
    QFile file("User.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)) {

        while (!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(" ");
            std::string loginFile = lst.at(0).toUtf8().constData();//Login
            std::string passwordFile = lst.at(1).toUtf8().constData();//Password

            if (login == loginFile)
            {
                file.close();
                controller.response(idClient, OperationCreator::createRegistrationResponse(Process::Failed));
                return;
            }
        }
        //Запись в файл
        finishStr = login + " " + password + "\n";
        QString str = QString::fromStdString(finishStr);
        QTextStream writeStream(&file);
        writeStream << str;
        file.close();
        controller.response(idClient, OperationCreator::createRegistrationResponse(Process::Success));
        return;

    }
    else
    {
        qDebug() << "Error FILE";
    }
    controller.response(idClient, OperationCreator::createRegistrationResponse(Process::Failed));
}

void Application::findGame(int idClient, Parametrs parametrs)
{
    (*findGameUsers)[idClient] = new User("User");
    if (findGameUsers->size() > 1)
    {
        
    }
}

void Application::startGame(int idClient1, int idClient2)
{
}

void Application::enterCell(int idClient, Parametrs parametrs)
{
    if (parametrs.find("Index") == parametrs.end())
    {
        controller.response(idClient, OperationCreator::createErrorResponse("Incorrect parametrs"));
        return;
    }

}

