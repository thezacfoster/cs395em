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

	//Place Creations
	Action("CreatePlace(BobsHouse, Cottage)");
	Action("CreatePlace(Prison, Dungeon)");
	Action("CreatePlace(Newcity, City)");
	//Bob Character
	Action("CreateCharacter(Bob, B)");
	Action("SetClothing(Bob, Peasant)");
	Action("SetHairStyle(Bob, Short_Full)");
	Action("SetPosition(Bob, BobsHouse.Door)");
	//Tom Character
	Action("CreateCharacter(Tom, D)");
	Action("SetClothing(Tom, HeavyArmour)");
	Action("SetHairStyle(Tom, Short_Full)");
	//Mary Character
	Action("CreateCharacter(Mary, C)");
	Action("SetClothing(Mary, Peasant)");
	Action("SetHairStyle(Mary, long)");
	Action("SetPosition(Mary, Newcity.Plant)");
	//Items
	Action("CreateItem(Refreshment, BluePotion)");
	Action("SetPosition(Refreshment, BobsHouse.Shelf)");	
	Action("CreateItem(Menacing Sword, Sword)");
	Action("CreateItem(Mysterious Book, BlueBook)");
	//Icons
	Action("EnableIcon(Take_Flask, Flask, Refreshment, Take Refreshment, true)");
	Action("EnableIcon(Open_Door, Open, BobsHouse.Door, Leave the house, true)");
	Action("EnableIcon(Talk_To_Mary, Talk, Mary, Talk To Mary, true)");
	//Menu
	Action("ShowMenu()");
	//Inventories
	vector<string> playerInv;
	vector<string> chestInv;
	chestInv.push_back("Menacing Sword");
	chestInv.push_back("Mysterious Book");

	// Respond to input.
	while (true) {
		string i;
		getline(cin, i);
		if (i == "input Selected Start") {
			Action("SetCameraFocus(Bob)");
			Action("HideMenu()");
			Action("EnableInput()");
		}
		
		//------------------Dialogue For Mary------------------
		else if (i == "input Talk_To_Mary Mary") {
			Action("ClearDialog()");
			Action("ShowDialog()");
			Action("SetRight(Mary)");
			Action("SetLeft(Bob)");
			//if have book
			Action("SetDialog(May I see your book? [yes|Sure!] [no|No...])");
			//else dont have book
			Action("SetDialog(I love to discuss books! [ok|Let me see if I can find one!])");
		}

		else if (i == "input Selected yes") {
			Action("ClearDialog()");
			Action("SetDialog(It speaks of an enchantment spell for a sword! [cool|I think I have a sword at home.])");
		}

		else if (i == "input Selected ok") {
			Action("HideDialog()");
		}

		else if (i == "input Selected cool") {
			Action("HideDialog()");
		}

		else if (i == "input Selected no") {
			Action("HideDialog()");
		}
		//------------------Dialogue For Mary------------------

		else if (i == "input Take_Flask Refreshment") {
			Action("Take(Bob, Refreshment, BobsHouse.Shelf)");
			Action("Pocket(Bob, Refreshment)");
			playerInv.push_back("Refreshment");
			//Action("DisableIcon(Pickup_Key, BobsHouse.Shelf)");
			//Action("SetPosition(HouseKey)");
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
		//Leaving house with at least one item
		else if (i == "input Open_Door BobsHouse.Door") {
			bool hasSomething = false;
			if (playerInv.size() >= 1) {
					hasSomething = true;
				}
			if (hasSomething == true) {
				Action("Exit(Bob, BobsHouse.Door, true)");
				Action("FadeOut()");
				Action("DisableInput()");
				Action("SetPosition(Bob, Newcity.BlueHouseDoor)");
				Action("FadeIn()");
				Action("Enter(Bob, Newcity.BlueHouseDoor, true)");
				Action("EnableInput()");
			}
			else {
				Action("SetNarration(You feel like a you need to take something with you.)");
				Action("ShowNarration()");
			}
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

