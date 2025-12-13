#include "UI.h"

// Helper: Print comma separated IDs
template <typename T>
void printIDs(LinkedQueue<T*>* list) {
	int count = list->getCount();
	LinkedQueue<T*> temp;
	T* item;

	cout << "[";
	for (int i = 0; i < count; i++) {
		list->dequeue(item);
		if (i > 0) cout << ", ";
		cout << item->getID();
		temp.enqueue(item);
	}
	cout << "]";

	while (!temp.isEmpty()) {
		temp.dequeue(item);
		list->enqueue(item);
	}
}

// Helper: Print Detailed Info
void printDetailed(PriQueue<mission*>* list, int currentDay) {
	int count = list->getCount();
	PriQueue<mission*> temp;
	mission* m;
	int priority;

	int i = 0;
	while (list->dequeue(m, priority)) {
		if (i > 0) cout << " ";

		int daysLeft = (-priority) - currentDay;
		if (daysLeft < 0) daysLeft = 0;

		cout << "[" << m->getID() << "/" << m->getRover()->getID() << ", " << daysLeft << "days]";
		temp.enqueue(m, priority);
		i++;
	}

	while (temp.dequeue(m, priority)) {
		list->enqueue(m, priority);
	}
}

// Helper: Print Requests
void printRequests(LinkedQueue<request*>* requests) {
	int count = requests->getCount();
	LinkedQueue<request*> temp;
	request* req;
	int limit = 10;

	int i = 0;
	while (i < count) {
		requests->dequeue(req);
		if (i < limit) {
			if (i > 0) cout << ", ";

			newRequest* nr = dynamic_cast<newRequest*>(req);
			if (nr) cout << "[R," << nr->getMissionType() << "," << nr->getDay() << "," << nr->getMissionID() << "]";
			else cout << "[X," << req->getDay() << "," << req->getMissionID() << "]";
		}
		temp.enqueue(req);
		i++;
	}
	while (!temp.isEmpty()) {
		temp.dequeue(req);
		requests->enqueue(req);
	}
}

// Helper: Print Done IDs
void printDoneStack(ArrayStack<mission*>* stack) {
	int count = stack->getCount();
	ArrayStack<mission*> tempStack;
	mission* m;

	cout << "[";
	int i = 0;
	while (stack->pop(m)) {
		if (i > 0) cout << ", ";
		cout << m->getID();
		tempStack.push(m);
		i++;
	}
	cout << "]";

	while (tempStack.pop(m)) {
		stack->push(m);
	}
}

void UI::printDay(int day,
	LinkedQueue<request*>* requests,
	LinkedQueue<mission*>* r_nm, LinkedQueue<mission*>* r_pm, LinkedQueue<mission*>* r_dm,
	LinkedQueue<rover*>* a_nr, LinkedQueue<rover*>* a_pr, LinkedQueue<rover*>* a_dr,
	PriQueue<mission*>* out, PriQueue<mission*>* exec, PriQueue<mission*>* back,
	ArrayStack<mission*>* done,
	LinkedQueue<mission*>* aborted,
	LinkedQueue<rover*>* c_nr, LinkedQueue<rover*>* c_pr, LinkedQueue<rover*>* c_dr)
{
	cout << "Current Day: " << day << endl;

	cout << "================ Requests List ================" << endl;
	cout << requests->getCount() << " requests remaining: "; printRequests(requests); cout << endl;

	int totalReady = r_nm->getCount() + r_pm->getCount() + r_dm->getCount();
	cout << "================ Ready List(s) ================" << endl;
	cout << totalReady << " Missions: ";
	cout << "NMs"; printIDs(r_nm); cout << " PMs"; printIDs(r_pm); cout << " DMs"; printIDs(r_dm); cout << endl;

	int totalAvail = a_nr->getCount() + a_pr->getCount() + a_dr->getCount();
	cout << "================ Available Rovers List(s) ================" << endl;
	cout << totalAvail << " Available Rovers: ";
	cout << "NR"; printIDs(a_nr); cout << " PR"; printIDs(a_pr); cout << " DR"; printIDs(a_dr); cout << endl;

	cout << "================ OUT List(s) ================" << endl;
	cout << out->getCount() << " Missions/Rovers: "; printDetailed(out, day); cout << endl;

	cout << "================ EXEC List(s) ================" << endl;
	cout << exec->getCount() << " Missions/Rovers: "; printDetailed(exec, day); cout << endl;

	cout << "================ BACK List(s) ================" << endl;
	cout << back->getCount() << " Missions/Rovers: "; printDetailed(back, day); cout << endl;

	cout << "================ Aborted List(s) ================" << endl;
	cout << aborted->getCount() << " Missions: "; printIDs(aborted); cout << endl;

	int totalCheck = c_nr->getCount() + c_pr->getCount() + c_dr->getCount();
	cout << "================ Checkup List(s) ================" << endl;
	cout << totalCheck << " Rovers: ";
	cout << "NR"; printIDs(c_nr); cout << " PR"; printIDs(c_pr); cout << " DR"; printIDs(c_dr); cout << endl;

	cout << "================ DONE List(s) ================" << endl;
	cout << done->getCount() << " Missions: "; printDoneStack(done); cout << endl;
}