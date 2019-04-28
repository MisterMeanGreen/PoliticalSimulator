// Political Simulator.cpp : Defines the entry point for the console application.
//Nicholas Dundas
//Game about controlling the USA
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Standards.h"
using namespace std;

class USA {
	struct coord { int x; int y; };
private:
		class state {
			int population;
			int income;
			vector<string> neighbors;
			//vector< coord > pixels TODO;
			int my_id;
			static int pub_id() {
				static int ID = 0;
				return ID++;
			}
			public:
				int clique_id; //current clique id controlling it
				string name; //name of state
				state(int p_id, string p_name) : my_id(pub_id()) {
					
					clique_id = p_id;
					name = p_name;
					
				}
				~state() {}
				void set_neighbor(string p_id) {
					neighbors.push_back(p_id);
				}

				auto get_neighbors() {
					return neighbors;
				}
				auto get_id() {
					return my_id;
				}

		};
vector<state> states;

public:

};


int main()
{
	try {
		person::load_player_files();
	}
	catch (string test) {
		cout << test;
	}

}

