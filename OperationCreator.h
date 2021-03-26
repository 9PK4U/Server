#pragma once 
#include "Operation.h"
#include <list>


using std::list;
enum class Process {Success, Failed};

class OperationCreator
{
public:
	Operation createAutorizationResponse(Process process, string details = "");
	Operation createRegistrationResponse(Process process, string details = "");
	Operation createEnterCellResponse(string value, string map);
	Operation createGetStatisticResponse(list<string> staticticList);
	Operation createFindGameResponse(string id, string playerName1, string playerName2, string map, string currentStep);
	Operation createStasusGameResponse(string pointsPlayer1, string pointsPlayer2, string currentStep);
	Operation createEndGameResponse(string details = "");


private:
};