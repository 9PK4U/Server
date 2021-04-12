#include "OperationCreator.h"

Operation OperationCreator::createAutorizationResponse(Process process, string details)
{
    Parametrs params{
        { "Process" ,process==Process::Success?"Success":"Failed" },
        { "Details" ,details }
    };
    return Operation(Operation::Type::Autorization, params);
}

Operation OperationCreator::createRegistrationResponse(Process process, string details)
{
    Parametrs params{ 
        { "Process" ,process == Process::Success ? "Success" : "Failed" },
        { "Details" ,details } 
    };
    return Operation(Operation::Type::Registration, params);
}

Operation OperationCreator::createEnterCellResponse(GameContext context)
{
    Parametrs params{ 
        { "Index" ,context.lastIndexCell },
        { "Value" ,context.lastPoint },
        { "CurrentStep" ,context.currentStepPlayerName },
        { "StatusGame" , context.statusGame }
    };
    return Operation(Operation::Type::EnterCell, params);
}

Operation OperationCreator::createGetStatisticResponse(list<string> staticticList)
{
    string strStatistic;
    for (auto i : staticticList)
    {
        strStatistic += i + '\n';
    }
    Parametrs params{ { "Statistic", strStatistic} };
    return Operation(Operation::Type::GetStatistic, params);
}

Operation OperationCreator::createFindGameResponse(string id, string playerName1, string playerName2, string currentStep)
{
    Parametrs params{
        { "Id" ,id },
        { "PlayerName1" ,playerName1 },
        { "PlayerName2" ,playerName2 },
        { "CurrentStep" ,currentStep }
    };
    return Operation(Operation::Type::FindGame, params);
}

Operation OperationCreator::createStasusGameResponse(string pointsPlayer1, string pointsPlayer2, string currentStep)
{
    Parametrs params{ 
        { "PointsPlayer1" ,pointsPlayer1 },
        { "PointsPlayer2" ,pointsPlayer2 } ,
        { "CurrentStep" ,currentStep } ,
    };
    return Operation(Operation::Type::StatusGame, params);
}

Operation OperationCreator::createEndGameResponse(string details)
{
    Parametrs params{ { "Details" ,details} };
    return Operation(Operation::Type::EndGame, params);
}

Operation OperationCreator::createErrorResponse(string details)
{
    Parametrs params{ { "Details" ,details} };
    return Operation(Operation::Type::Error, params);
}
