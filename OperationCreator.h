#pragma once 
#include "Operation.h"
#include <list>


using std::list;
enum class Process {Success, Failed};

class OperationCreator
{
public:
	static Operation createAutorizationResponse(Process process, string details = "");
	static Operation createRegistrationResponse(Process process, string details = "");
	static Operation createEnterCellResponse(string value, string map);
	static Operation createGetStatisticResponse(list<string> staticticList);
	static Operation createFindGameResponse(string id, string playerName1, string playerName2, string map, string currentStep);
	static Operation createStasusGameResponse(string pointsPlayer1, string pointsPlayer2, string currentStep);
	static Operation createEndGameResponse(string details = "");
	static Operation createErrorResponse(string details = "");


private:
};