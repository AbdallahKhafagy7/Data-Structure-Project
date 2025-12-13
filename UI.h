#pragma once
#include <iostream>
#include "LinkedQueue.h"
#include "PriQueue.h"
#include "ArrayStack.h"
#include "mission.h"
#include "rover.h"
#include "request.h"
#include "newRequest.h"
#include "abortRequest.h"

using namespace std;

class UI {
public:
	void printDay(int day,
		LinkedQueue<request*>* requests,
		LinkedQueue<mission*>* r_nm, LinkedQueue<mission*>* r_pm, LinkedQueue<mission*>* r_dm,
		LinkedQueue<rover*>* a_nr, LinkedQueue<rover*>* a_pr, LinkedQueue<rover*>* a_dr,
		PriQueue<mission*>* out, PriQueue<mission*>* exec, PriQueue<mission*>* back,
		ArrayStack<mission*>* done,
		LinkedQueue<mission*>* aborted,
		LinkedQueue<rover*>* c_nr, LinkedQueue<rover*>* c_pr, LinkedQueue<rover*>* c_dr);
};