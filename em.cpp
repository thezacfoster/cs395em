#include <iostream>
#include <string>
#include <vector>

#include "GuardBehavior.h"

using namespace std;

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
	Action("SetPosition(Tom, Newcity.WestEnd)");
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
	Action("EnableIcon(Open_Door, Open, Newcity.BlueHouseDoor, Enter the house, true)");
	Action("EnableIcon(Open_Chest, Open, BobsHouse.Chest, Open the chest, true)");
	Action("EnableIcon(Take_Sword, Hand, Menacing Sword, Take the sword, true)");
	Action("EnableIcon(Take_Book, Hand, Mysterious Book, Take the book, true)");
	Action("EnableIcon(Talk_To_Mary, Talk, Mary, Talk To Mary, true)");
	//Menu
	Action("ShowMenu()");
	//Inventories
	vector<string> playerInv;
	vector<string> chestInv;
	chestInv.push_back("Menacing Sword");
	chestInv.push_back("Mysterious Book");

	bool hasSword = false;
	bool hasBook = false;

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
			if (hasBook) {
				Action("SetDialog(May I see your book? [yes|Sure!] [no|No...])");
			}
			else {
				Action("SetDialog(I love to discuss books! [ok|Let me see if I can find one!])");
			}
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
		//-----------------Inventories--------------------
		else if (i == "input Open_Chest BobsHouse.Chest") {
			Action("WalkTo(Bob, BobsHouse.Chest)");
			Action("OpenFurniture(Bob, BobsHouse.Chest)");
			for (string item : chestInv) {
				Action("AddToList(" + item + ")");
			}
			Action("ShowList(BobsHouse.Chest)");
		}
		else if (i == "input Key Inventory") {
			for (string item : playerInv) {
				Action("AddToList(" + item + ")");
				//action('DisableInput()')
			}
			Action("ShowList(Bob)");
		}
		else if (i == "input Close List") {
			Action("HideList()");
			Action("ClearList()");
			Action("EnableInput()");
		}
		//---------------Chest Interactions---------------
		else if (i == "input Take_Sword Menacing Sword") {
			Action("HideList()");
			Action("SetDialog(A rather menacing-looking sword. Take it? [TakeSword|Yes] [LeaveSword|No])");
			Action("ShowDialog()");
		}
		else if (i == "input Selected TakeSword") {
			Action("HideDialog()");
			Action("ClearDialog()");
			Action("ShowList(Bob)");
			Action("RemoveFromList(Menacing Sword)");
			for (int i = 0; i < chestInv.size(); i++) {
				if (chestInv[i] == "Menacing Sword") {
					chestInv.erase(chestInv.begin() + i);
				}
			}
			Action("DisableIcon(Take_Sword, Menacing Sword)");
			playerInv.push_back("Menacing Sword");

			Action("EnableIcon(ReturnSword, Hand, BobsHouse.Chest, Return the sword, false)");
		}
		else if (i == "input Selected LeaveSword") {
			Action("HideDialog()");
			Action("ClearDialog()");
			Action("ShowList(Bob)");
		}
		else if (i == "input ReturnSword BobsHouse.Chest") {
			// Put function causes big error
			//Action("Put(Bob, Menacing Sword, BobsHouse.Chest");
			Action("WalkTo(Bob, BobsHouse.Chest)");
			for (int i = 0; i < playerInv.size(); i++) {
				if (playerInv[i] == "Menacing Sword") {
					playerInv.erase(playerInv.begin() + i);
				}
			}
			chestInv.push_back("Menacing Sword");
			
			// can't be re-enabled?
			//Action("EnableIcon(Take_Sword, Hand, Menacing Sword)");
		}
		else if (i == "input Take_Book Mysterious Book") {
			Action("HideList()");
			Action("SetDialog(A mysterious book written in an unrecognizable language. Take it? [TakeBook|Yes] [LeaveBook|No])");
			Action("ShowDialog()");
		}
		else if (i == "input Selected TakeBook") {
			Action("HideDialog()");
			Action("ClearDialog()");
			Action("ShowList(Bob)");
			Action("RemoveFromList(Mysterious Book)");
			for (int i = 0; i < chestInv.size(); i++) {
				if (chestInv[i] == "Mysterious Book") {
					chestInv.erase(chestInv.begin() + i);
				}
			}
			Action("DisableIcon(Take_Book, Mysterious Book)");
			playerInv.push_back("Mysterious Book");
		}
		else if (i == "input Selected LeaveSword") {
			Action("HideDialog()");
			Action("ClearDialog()");
			Action("ShowList(Bob)");
		}

		//Leaving house with at least one item
		else if (i == "input Open_Door BobsHouse.Door") {
			bool hasSomething = false;
			if (playerInv.size() >= 1) {
					hasSomething = true;
			}
			if (hasSomething == true) {
				//bool hasSword = false;
				for (string item : playerInv) {
					if (item == "Menacing Sword") {
						hasSword = true;
					}
					if (item == "Mysterious Book") {
						hasBook = true;
					}
				}
				if (hasSword) {
					Action("SetDialog(Are you sure you want to leave carrying the sword? [Leave|Yes] [DontLeave|No])");
					Action("ShowDialog()");
				}
				else {
					Action("Exit(Bob, BobsHouse.Door, true)");
					Action("FadeOut()");
					Action("DisableInput()");
					Action("SetPosition(Bob, Newcity.BlueHouseDoor)");
					Action("FadeIn()");
					Action("Enter(Bob, Newcity.BlueHouseDoor, true)");
					Action("EnableInput()");
					OutsideSequence(hasSword);
				}
			}
			else {
				Action("SetNarration(You feel like a you need to take something with you.)");
				Action("ShowNarration()");
			}
		}
		else if (i == "input Selected Leave") {
			Action("HideDialog()");
			Action("ClearDialog()");
			Action("Exit(Bob, BobsHouse.Door, true)");
			Action("FadeOut()");
			Action("DisableInput()");
			Action("SetPosition(Bob, Newcity.BlueHouseDoor)");
			Action("FadeIn()");
			Action("Enter(Bob, Newcity.BlueHouseDoor, true)");
			Action("EnableInput()");
			OutsideSequence(hasSword);
		}
		else if (i == "input Open_Door Newcity.BlueHouseDoor") {
			Action("Exit(Bob, Newcity.BlueHouseDoor, true)");
			Action("FadeOut()");
			Action("DisableInput()");
			Action("SetPosition(Bob, BobsHouse.Door)");
			Action("Enter(Bob, BobsHouse.Door, true)");
			Action("FadeIn()");
			Action("EnableInput()");
		}
		else if (i == "input Selected DontLeave") {
			Action("HideDialog()");
			Action("ClearDialog()");
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

