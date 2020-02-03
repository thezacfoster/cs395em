#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Test Commit
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

int main() {

	// Set up a small house with a door.
	Action("CreatePlace(BobsHouse, Cottage)");
	Action("CreatePlace(Prison, Dungeon)");
	Action("CreateCharacter(Bob, B)");
	Action("SetClothing(Bob, Peasant)");
	Action("SetHairStyle(Bob, Short_Full)");
	Action("SetPosition(Bob, BobsHouse.Door)");
	Action("CreateCharacter(Tom, D)");
	Action("SetClothing(Tom, HeavyArmour)");
	Action("SetHairStyle(Tom, Short_Full)");
	Action("CreateCharacter(Mary, C)");
	Action("SetClothing(Mary, Witch)");
	Action("SetHairStyle(Mary, long)");
	Action("SetPosition(Mary, BobsHouse.Door)");
	Action("CreateItem(HouseKey, BlueKey)");
	Action("SetPosition(HouseKey, BobsHouse.Shelf)");
	Action("EnableIcon(\"Pickup_Key\", Hand, BobsHouse.Shelf, \"Pick up key\", true)");
	Action("EnableIcon(\"Open_Door\", Open, BobsHouse.Door, \"Leave the house\", true)");
	Action("ShowMenu()");

	vector<string> playerInv;

	// Respond to input.
	while (true) {
		string i;
		getline(cin, i);
		if (i == "input Selected Start") {
			Action("SetCameraFocus(Bob)");
			Action("HideMenu()");
			Action("EnableInput()");
		}
		else if (i == "input \"Pickup_Key\" BobsHouse.Shelf") {
			playerInv.push_back("HouseKey");
			Action("DisableIcon(\"Pickup_Key\", BobsHouse.Shelf)");
			Action("SetPosition(HouseKey)");
		}
		else if (i == "input Key Inventory") {
			for (string item : playerInv) {
				Action("AddToList(" + item + ")");
				//action('DisableInput()')
				Action("ShowList(Bob)");
			}
		}
		else if (i == "input Close List") {
			Action("HideList()");
			Action("ClearList()");
		}
		else if (i == "input \"Open_Door\" BobsHouse.Door") {
			bool hasKey = false;
			for (string item : playerInv) {
				if (item == "HouseKey") {
					hasKey = true;
				}
			}
			if (hasKey == true) {
				Action("Exit(Bob, BobsHouse.Door, true)");
				Action("CreatePlace(City, Newcity)");
				Action("Enter(Bob, City.Door, true)");
			}
			else {
				Action("SetNarration(\"The door is locked!\")");
				Action("ShowNarration()");
			}
		}
		else if (i == "input arrived Bob position Farm.Exit") {
			//Action("Exit(Bob, Farm.Exit, true)");
			Action("FadeOut()");
			Action("DisableInput()");
			Action("CreatePlace(Forest, ForestPath)");
			Action("Enter(Bob, Forest.EastEnd, true)");
			Action("EnableInput()");
		}
		else if (i == "input arrived Bob position Forest.WestEnd") {
			//Action("Exit(Bob, Forest.WestEnd, true)");
			Action("FadeOut()");
			Action("DisableInput()");
			Action("CreatePlace(City, City)");
			Action("Enter(Bob, City.EastEnd, true)");
			Action("EnableInput()");
		}
		else if (i == "input Key Pause") {
			Action("DisableInput()");
			Action("ShowMenu()");
		}
		else if (i == "input Selected Resume") {
			Action("SetCameraFocus(Bob)");
			Action("HideMenu()");
			Action("EnableInput()");
		}
		else if (i == "input Close Narration") {
			Action("HideNarration()");
		}
		else if (i == "input Selected Quit") {
			Action("Quit()");
		}
	}

	return 0;
}

