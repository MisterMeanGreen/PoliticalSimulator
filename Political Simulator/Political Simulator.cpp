// Political Simulator.cpp : Defines the entry point for the console application.
//Nicholas Dundas
//Game about controlling the USA
//4/29/2018
#include <Windows.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Standards.h"
#include "Unicode.h"
using namespace std;



int main()
{
	init_locale();
	Map USA;
	USA.load_map_files();
	person::load_player_files();
	wcout << L"\n" << USA.display;
	for (auto state : USA.states) {
		USA.render_state(state.name,L'A');
	}
	int j;
	wcin >> j;
}

