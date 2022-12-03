#pragma once
#include<iomanip>
#include<iostream>
#include<String>
#include<vector>
#include "game.h"
using namespace std;

class player {

	private:
		string name;
		int jerseyNum;
		//vector<int> mvpGames;			//Final version, using game version for testing
		vector<game> mvpGames;
	public:


		player(string _name, int _jerseyNum) {
			this->name = _name;
			this->jerseyNum = _jerseyNum;
		};
		
		player() {
			this->name = "";
			this->jerseyNum = 0;
		};

		string getName() {
			return this->name;
		}

		int getJerseyNum() {
			return this->jerseyNum;
		}

		int getVectorSize() {
			return mvpGames.size();
		}

		void addID(game game) {
			mvpGames.push_back(game);
		}

		game accessElementAt(int i) {
			return mvpGames[i];
		}
		vector<game> getVector() {
			return this->mvpGames;
		}

		//void addID(int ID) {				//Final version, using game version for testing
		//	mvpGames.push_back(ID);
		//}
		//int accessElementAt(int i) {
		//	return mvpGames[i];
		//}
	
};