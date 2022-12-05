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
		vector<int> mvpGames;			

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

		vector<int> getVector() {
			return this->mvpGames;
		}

		void addID(int ID) {
			mvpGames.push_back(ID);
		}
		int accessElementAt(int i) {
			return mvpGames[i];
		}
	
};