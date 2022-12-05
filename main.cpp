#include<iomanip>
#include<iostream>
#include<map>
#include <fstream>
#include <sstream>

#include "player.h"
#include "game.h"
#include "RedBlackTree.h"

using namespace std;

int main() {
	void printMenu();
	map<string, player> playersContainer;
	map<string, player>::iterator it;
	string firstName, lastName;
	int menuOp = -1, tempID, treeSelection;

	//RB tree
	redBlack rbTree;
	RedBlackNode* tempRBN = nullptr;
	RedBlackNode* root = nullptr;

	//////////////Load Data//////////////
	fstream Rfile("Roster.csv", ios::in);
	fstream Gfile("GamesData.csv", ios::in);
	
	if (Rfile.is_open())
	{
		string tempName, tempNum;
		getline(Rfile, tempName); //skips first line which is heading
		for (int i = 0; i <= 15; i++) {
			getline(Rfile, tempName,',');
			getline(Rfile, tempNum);
			player tempPlayerObj = player(tempName, stoi(tempNum));
			playersContainer[tempName] = tempPlayerObj;

		}
		
	}
	else {
		cout << "Error in opening \"Roster.csv\"\n";
	}

	if (Gfile.is_open())
	{
		string home, away, hScore, aScore, MVP, p, a, r, b, s, TO, f, sp, gameID;

		getline(Gfile, home); //skips first line which are heading

		for (int i = 0; i < 100000; i++) {
			getline(Gfile,home, ',');
			getline(Gfile, away, ',');
			getline(Gfile, hScore, ',');
			getline(Gfile, aScore, ',');
			getline(Gfile, MVP, ',');
			getline(Gfile, p, ',');
			getline(Gfile, a, ',');
			getline(Gfile, r, ',');
			getline(Gfile, b, ',');
			getline(Gfile, s, ',');
			getline(Gfile, TO, ',');
			getline(Gfile, f, ',');
			getline(Gfile, sp, ',');
			getline(Gfile, gameID);

			
			game tempGameObj = game(home, away, stoi(hScore), stoi(aScore), MVP, stoi(p), stoi(a), stoi(r), stoi(b), stoi(s), stoi(TO), stoi(f), stod(sp), stoi(gameID));
			//insertion of tempGameObj into B-tree
			rbTree.InsertHelp(tempGameObj, stoi(gameID));
			playersContainer.find(MVP)->second.addID(stoi(gameID));
	
		}

	}
	else {
		cout << "Error in opening \"GamesdATA.csv\"\n";
	}
	



	/////////////////Menu/////////////////

	cout << "(Current Trees loaded: Red/Black Tree and B-Tree)\n\n";
	cout << "Welcome to the Miami Heat Game Tracker! \n";

	while (menuOp != 6) {
		printMenu();
		cin >> menuOp;
		cout << endl;
		switch (menuOp) {
		case 1:
			cout << "Current Roster\n";
			for (it = playersContainer.begin(); it != playersContainer.end(); it++) {
				cout << it->first << " (Jersey Number: " << it->second.getJerseyNum() << ")\n";
			}
			cout << endl;
			break;

		case 2:
			cout << "Player Name: ";

			cin >> firstName >> lastName;
			cout << endl;
			it = playersContainer.find(firstName + " " + lastName);
			while (it == playersContainer.end()) { //checks for valid Name 
				cout << "Player does not Exist \n";
				cout << "Player Name: ";
				cin >> firstName >> lastName;
				it = playersContainer.find(firstName + " " + lastName);
			}

			cout << "Loading data for " << it->first << "...\n";
			cout << "-------------------------------------------------------------------------------------------------------\n";
			for (int i = 0; i < it->second.getVectorSize(); i++) {

				int tempID = it->second.accessElementAt(i);
				tempRBN = rbTree.searchHelper(tempID);
				if (tempRBN != nullptr) {
					tempRBN->gameObj.printData();
				}
				cout << endl;
			}
			cout << "\n" << it->second.getVectorSize() << " games loaded\n";
			cout << endl;
			break;


		case 3:
			cout << "Game ID: ";
			cin >> tempID;
			while ((tempID < 100000) || (tempID > 200000)) { //checks for valid ID 
				cout << "Invalid ID (Valid IDs range from 100000-200000)\n";
				cout << "Game ID (Valid IDs range from 100000-200000): ";
				cin >> tempID;
			}
			

			//timer start
			//game temp = BTree.searchID(tempID)
			// temp.printData();
			// timer stop
			// print timer
			// 
			cout << "-------------------------------------------------------------------------------------------------------\n";
			tempRBN = rbTree.searchHelper(tempID);
			if (tempRBN != nullptr) {
				tempRBN->gameObj.printData();
				//cout << tempRBN->left->ID << " " << tempRBN->right->ID << endl;
			}
			else {
				cout << "ID not found\n";
			}
			
			

			cout<<"Red and Black Tree returned result in: "  << " seconds" << endl;
			//print timer

			break;

		case 4:
			cout << "Please Select a Tree to use:\n 1. Red/Black Tree\n 2. B-Tree\n";
			cout << "Selection: ";
			cin >> treeSelection;
			cout << "Player name: ";
			cin >> firstName >> lastName;
			cout << endl;
			it = playersContainer.find(firstName + " " + lastName);
			while (it == playersContainer.end()) { //checks for valid Name 
				cout << "Player does not Exist \n";
				cout << "Player Name: ";
				cin >> firstName >> lastName;
				it = playersContainer.find(firstName + " " + lastName);
			}

			cout << "Loading data for " << it->first << "...\n";
			cout << "-------------------------------------------------------------------------------------------------------\n";
			for (int i = 0; i < it->second.getVectorSize(); i++) {
				
				int tempID = it->second.accessElementAt(i);
				if (treeSelection == 1) {
					tempRBN = rbTree.searchHelper(tempID);
					if (tempRBN != nullptr) {
						tempRBN->gameObj.printData();
					}
				}
				else {
					cout << "B tree currently not implemented\n";

				}
				
				cout << endl;
			}
			cout << "\n" << it->second.getVectorSize() << " games loaded\n";
			cout << endl;
			break;

		case 5:
			cout << "Please Select a Tree to use:\n 1. Red/Black Tree\n 2. B-Tree\n";
			cout << "Selection: ";
			cin >> treeSelection;
			cout << "Game ID: ";
			cin >> tempID;
			while ((tempID < 100000) || (tempID > 200000)) {
				cout << "Invalid ID (Valid IDs range from 100000-200000)\n";
				cout << "Game ID: ";
				cin >> tempID;
			}
			cout << "-------------------------------------------------------------------------------------------------------\n";
			if (treeSelection == 1) {
				tempRBN = rbTree.searchHelper(tempID);
				tempRBN->gameObj.printData();
			}
			else {
				cout << "B tree currently not implemented\n";
			}
			
			break;
		case 6:
			cout << "Exiting...\n";
			break;
		}
		
	}

}

void printMenu() {

	cout << "Select an option:\n 1. Display Current Roster \n 2. Player Search (Only one that functions without tree) \n 3. Game ID Search \n 4. Player Search (using 1 tree) \n 5. Game ID Search (using 1 tree)\n 6. Exit\n";
	cout << "Selection: ";
}