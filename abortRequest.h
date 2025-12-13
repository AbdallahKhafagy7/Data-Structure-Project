#pragma once
#include <iostream>
#include "request.h"

// Forward declaration
class MarsStation;

class abortRequest : public request {
public:
	// Constructor Declaration
	abortRequest(MarsStation* s, char reqType, int id, int day);

	// Function Declaration only
	void Operate() override;
};