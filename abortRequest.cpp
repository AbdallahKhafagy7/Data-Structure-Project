#include "abortRequest.h"
#include "MarsStation.h" // <--- This includes the full definition, fixing the error

abortRequest::abortRequest(MarsStation* s, char reqType, int id, int day)
	: request(s, reqType, id, day)
{
}

void abortRequest::Operate() {
	if (station) {
		// Now the compiler knows exactly what MarsStation is
		station->AbortMission(missionID);
	}
}