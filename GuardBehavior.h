#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;


// Wait for given input before continueing
void WaitFor(string message) {
	while (true) {
		string i;
		getline(cin, i);
		if (i == message) {
			break;
		}
	}
}

// Send a command to Camelot.
void Action(string command) {
	cout << ("start " + command) << endl;
	WaitFor("succeeded " + command);
}

void SwordSequence() {
	//------------------Dialogue For Tom------------------
	bool Choice = false;
	Action("ShowDialog()");
	Action("SetRight(Tom)");
	Action("SetLeft(Bob)");
	Action("SetDialog(Stop! What are you doing outside brandishing a sword like that? [Resistance|Down with the Monarchy!] [Ego|I do what I want])");

	while (!Choice) {
		string i;
		getline(cin, i);
		if (i == "input Selected Resistance") {
			Action("ClearDialog()");
			Action("SetDialog(How dare you say something like that? You are going away for a long time! [Jail|I will never give up!])");
		}
		else if (i == "input Selected Ego") {
			Action("ClearDialog()");
			Action("SetDialog(We will see about that. To Jail with you! [Jail|Go to Jail])");
		}
		else if (i == "input Selected Jail") {
			Action("ClearDialog()");
			Choice = true;
		}
	}
	//------------------Send Player to Jail------------------
	Action("DisableInput()");
	Action("HideDialog()");
	Action("FadeOut()");
	Action("SetPosition(Bob, Prison.Bed)");
	Action("EnableIcon(Exit_Cell, Hand, Prison.CellDoor, Open Cell Door, true)");
	Action("SetCameraFocus(Bob)");
	Action("FadeIn()");
	Action("EnableInput()");
}
//------------------Takes Control away fro player on exiting house------------------
void OutsideSequence(bool SwordCheck) {
	if (SwordCheck) {
		Action("WalkTo(Tom, Bob)");
		Action("EnableInput()");
		SwordSequence();
	}
	Action("EnableInput()");
}
