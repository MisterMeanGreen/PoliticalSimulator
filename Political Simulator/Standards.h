#pragma once
//Where the main classes of our program go
//Such as USA, State, Person, and effect

#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include "Helper.h"
enum pol_genders
{
	Male = 0, Female = 1
};
enum pol_stat_ids {
	diplomacy = 0, intrigue = 1, appeal = 2, command = 3
};
class effect { //Used as traits
public:
	std::wstring name;
	std::wstring description;
	int diplomacy; //Ability for Person to work with other Politicians
	int intrigue; //Ability for Person to conduct spying and espioange
	int appeal; //Ability for person to appeal to the people
	int command; //Ability for Person to control others
	effect(std::wstring p_name, std::wstring p_desc, int p_diplo, int p_int, int p_app, int p_comm);
	std::vector<std::wstring> negative_traits; //Defines traits that the current trait cannot be in conjunction with
	effect();
	~effect();
	bool operator==(effect x);
	bool operator!=(effect x);
	bool contains_ntrait(std::wstring s);
};
class person {
	std::wstring first_name; //Usually Random
	std::wstring last_name; //Dynastys!
	uint32_t age; //Age
	bool gender; //Gender
	int money; //Moolah
	std::vector<effect> traits; //Traits affect stats and other things
	int diplomacy; //Ability for Person to work with other Politicians
	int intrigue; //Ability for Person to conduct spying and espioange
	int appeal; //Ability for person to appeal to the people
	int command; //Ability for Person to control others
	uint32_t id;
	void raw_add(effect trait);
	static uint32_t pub_id;
public:
	bool remove_trait(uint16_t trait_num); //Removes a Single Trait at Postion X
	bool remove_trait(std::wstring name); //Remove trait via name
	bool remove_trait(effect trait); //Remove trait via another trait
	bool add_trait_no_remove(effect trait); //Add a single trait
	bool add_trait(effect trait); //Add a single trait
	void generate_random_traits(); //Generates Randomized Traits
	void generate_random_stats();
	void generate_random_name();
	void clear_traits();
	int add_stat(uint8_t stat, int amount); //Change a one of the stats by amount	
	int get_stat(uint8_t stat);
	std::wstring get_first_name();
	std::wstring get_last_name();
	std::wstring get_name();
	int add_money(int amount);
	int get_money();
	int get_age();
	uint32_t get_id();
	std::wstring get_gender();
	auto& operator[](uint32_t c);
	auto& trait_list();
	person(std::wstring p_first_name, std::wstring p_last_name, uint32_t p_age, bool p_gender, int p_money, int p_diplomacy, int p_intrigue, int p_appeal, int p_command);
	person(std::wstring p_first_name, std::wstring p_last_name, uint32_t p_age, bool p_gender, int p_money);
	person(uint32_t p_age, int p_money);
	static void load_player_files(); //Loads traits file, names for both females and males, and the last names
	static effect load_trait(std::wifstream& file, wchar_t& last_char); //Loads traits from file
};
std::wostream &operator<<(std::wostream& os, effect const &temp_effect);
class map {
private:
	struct coord { coord(); ~coord(); int x; int y; };
	class state {
	public:
		int population;
		int income;
		std::vector<std::wstring> neighbors; //neighboring states
		std::vector<coord> pixels; //pixels on console
		int clique_id; //current clique id controlling it
		std::wstring name; //name of state
		state(int p_id, std::wstring p_name);
		state(int p_id);
		~state();
		const auto& get_neighbors();
	};
	state load_state(std::wifstream& file, wchar_t& last_char); //Load a singular state from a file
		

public:
	std::wstring display;
	std::vector<state> states;
	void load_map_files(); //Loads in the map_display and the states information within the map
	void render_state(std::wstring wstr, wchar_t chr, WORD color); //Render a Single State from the Map
};