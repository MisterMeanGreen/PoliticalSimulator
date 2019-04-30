#pragma once
//Where the main classes of our program go
//Such as USA, State, Person, and effect
#include "Standards.h"
std::random_device rand_dev;
std::default_random_engine gen(rand_dev());
std::uniform_int_distribution<int> dist(0, 99);
effect::effect(std::wstring p_name, std::wstring p_desc, int p_diplo, int p_int, int p_app, int p_comm) {
	name = p_name;
	description = p_desc;
	diplomacy = p_diplo;
	intrigue = p_int;
	appeal = p_app;
	command = p_comm;
}
effect::effect() {
	name = L"NULL";
	description = L"NULL";
	diplomacy = 0;
	intrigue = 0;
	appeal = 0;
	command = 0; //Debug values to easily tell what values have been set when debugging
}
effect::~effect() {}
bool effect::operator==(effect x) {
	return name == x.name;
}
bool effect::operator!=(effect x) {
	return name != x.name;
}
bool effect::contains_ntrait(std::wstring s) {
	for (auto x : negative_traits)
		if (x == s)
			return true;
	return false;
}
std::vector<effect> traits;
std::vector<std::wstring> m_names;
std::vector<std::wstring> f_names;
std::vector<std::wstring> l_names;
void person::raw_add(effect trait) {
	traits.push_back(trait);
	diplomacy += traits.back().diplomacy;
	intrigue += traits.back().intrigue;
	appeal += traits.back().appeal;
	command += traits.back().command;
}
bool person::remove_trait(uint16_t trait_num) {//Removes a Single Trait at Postion X
	if (trait_num < traits.size() - 1) {
		diplomacy -= traits[trait_num].diplomacy;
		intrigue -= traits[trait_num].intrigue;
		appeal -= traits[trait_num].appeal;
		command -= traits[trait_num].command;
		traits.erase(traits.begin() + trait_num);
		return true;
	}
	else return false;
}
bool person::remove_trait(std::wstring name) { //Remove trait via name
	auto trait_itt = traits.begin();
	uint16_t trait_num = 0;
	while (trait_itt->name != name && trait_num < (traits.size() - 1)) {
		trait_itt++;
		trait_num++;
	}
	return remove_trait(trait_num);
}
bool person::remove_trait(effect trait) { //Remove trait via another trait
	return remove_trait(trait.name);
}
bool person::add_trait_no_remove(effect trait) { //Add a single trait
	for (auto curr_trait : traits) {
		for (auto my_neg_trait : trait.negative_traits) {
			if (curr_trait.name == my_neg_trait) {
				remove_trait(curr_trait);
				return false;
			}
		}
		if (curr_trait == trait) {
			remove_trait(curr_trait);
			return false;
		}
		for (auto neg_trait : curr_trait.negative_traits) {
			if (neg_trait == trait.name) {
				remove_trait(neg_trait);
				return false;
			}
		}
	}
	raw_add(trait);
	return true;
}
bool person::add_trait(effect trait) { //Add a single trait
	for (auto curr_trait : traits) {
		for (auto my_neg_trait : trait.negative_traits) {
			if (curr_trait.name == my_neg_trait) return false;
		}
		if (curr_trait == trait) return false;
		for (auto neg_trait : curr_trait.negative_traits) {
			if (neg_trait == trait.name) return false;
		}
	}
	raw_add(trait);
	return true;
}
void person::generate_random_traits() {//Generates Randomized Traits
	std::uniform_int_distribution<int> rand(-4, 4);
	std::uniform_int_distribution<int> rand_trait_num(0, ::traits.size() - 1);
	for (int x = 0; x < (age / 10) + rand(gen); x++) {
		while (!add_trait_no_remove(::traits[rand_trait_num(gen)]));
	}
}
void person::generate_random_stats() {
	std::uniform_int_distribution<int> rand_stat(0, 3); //Random stat to upgrade
	std::uniform_int_distribution<int> rand_total(0, (age / 2) + 10); //Random total amount you can upgrade
	auto total = rand_total(gen);
	for (auto x = 0; x < total; x++)
		switch (rand_stat(gen)) { //Randomize Stat Generation
		case 0:
			diplomacy++;
			break;
		case 1:
			intrigue++;
			break;
		case 2:
			appeal++;
			break;
		case 3:
			command++;
			break;
		}
}
void person::generate_random_name() {
	if (gender == pol_genders::Male) {
		std::uniform_int_distribution<int> ListSize(0, m_names.size() - 1);
		first_name = m_names[ListSize(gen)];

	}
	else {
		std::uniform_int_distribution<int> ListSize(0, f_names.size() - 1);
		first_name = f_names[ListSize(gen)];
	}
	std::uniform_int_distribution<int> ListSize(0, l_names.size() - 1);
	last_name = l_names[ListSize(gen)];
}
void person::clear_traits() {
	while (!traits.empty()) {
		diplomacy -= traits.back().diplomacy;
		intrigue -= traits.back().intrigue;
		appeal -= traits.back().appeal;
		command -= traits.back().command;
		traits.pop_back();
	}
}
int person::add_stat(uint8_t stat, int amount) { //Change a one of the stats by amount
	switch (stat) {
	case pol_stat_ids::diplomacy:
		return diplomacy += amount;
	case pol_stat_ids::intrigue:
		return intrigue += amount;
	case pol_stat_ids::appeal:
		return appeal += amount;
	case pol_stat_ids::command:
		return command += amount;
	}
	return 0;
}
int person::get_stat(uint8_t stat) {
	switch (stat) {
	case pol_stat_ids::diplomacy:
		return (diplomacy + abs(diplomacy)) / 2;
	case pol_stat_ids::intrigue:
		return (intrigue + abs(intrigue)) / 2;
	case pol_stat_ids::appeal:
		return (appeal + abs(appeal)) / 2;
	case pol_stat_ids::command:
		return (command + abs(command)) / 2;
	}
	return -1;
}
uint32_t person::pub_id;
std::wstring person::get_first_name() { return first_name; }
std::wstring person::get_last_name() { return last_name; }
std::wstring person::get_name() { return get_first_name() + L' ' + get_last_name(); }
int person::add_money(int amount) { return money += amount; }
int person::get_money() { return money; }
int person::get_age() { return age; }
uint32_t person::get_id() { return id; }
std::wstring person::get_gender() { return (gender == pol_genders::Male ? L"male" : L"female"); }
auto& person::operator[](uint32_t c) { return traits[c]; }
auto& person::trait_list() { return traits; }
person::person(std::wstring p_first_name, std::wstring p_last_name, uint32_t p_age, bool p_gender, int p_money, int p_diplomacy, int p_intrigue, int p_appeal, int p_command) : id(++pub_id) {
	first_name = p_first_name;
	last_name = p_last_name;
	age = p_age;
	gender = p_gender;
	money = p_money;
	diplomacy = p_diplomacy;
	intrigue = p_intrigue;
	appeal = p_appeal;
	command = p_command;
	generate_random_traits();
} //Manual Stats
person::person(std::wstring p_first_name, std::wstring p_last_name, uint32_t p_age, bool p_gender, int p_money) : id(++pub_id) {
	first_name = p_first_name;
	last_name = p_last_name;
	age = p_age;
	gender = p_gender;
	money = p_money;
	diplomacy = 0;
	intrigue = 0;
	appeal = 0;
	command = 0;
	generate_random_stats();
	generate_random_traits();
} //Generate Random Traits and Stats
person::person(uint32_t p_age, int p_money) : id(++pub_id) {
	age = p_age;
	int j = dist(gen);
	if (j < 95) {
		gender = pol_genders::Male;
	}
	else {
		gender = pol_genders::Female;
	}
	generate_random_name();
	money = p_money;
	diplomacy = 0;
	intrigue = 0;
	appeal = 0;
	command = 0;
	generate_random_stats();
	generate_random_traits();
} //Generate Random Traits and Stats
void person::load_player_files() { //Loads traits file, names for both females and males, and the last names
	std::wifstream file(L"traits.txt");
	std::wstring current_text;
	wchar_t last_char;
	auto load_until = [&](std::wstring chars) { return search_until(file, chars, last_char); };
	auto load_string = [&]() { return load_quotes(file, last_char); };
	try { //Attempt to load traits
		load_until(L"T");
		load_until(L"{");
		while (last_char != L'}') { //Load traits
			::traits.push_back(person::load_trait(file, last_char));
		}
	}
	catch (std::wstring error_recieved) {
		throw L"ERROR : Failed to load Traits file\n" + error_recieved;
	}
	file.close();
	file.open("names.txt"); //Load names
	try {
		load_until(L"M");
		load_until(L"{");
		do {
			m_names.push_back(load_until(L",}"));
		} while (last_char != '}');
	}
	catch (std::wstring error_recieved) {
		throw L"ERROR : Failed to load male names\n" + error_recieved;
	}
	try {
		load_until(L"F");
		load_until(L"{");
		do {
			f_names.push_back(load_until(L",}"));
		} while (last_char != '}');
	}
	catch (std::wstring error_recieved) {
		throw L"ERROR : Failed to load female names\n" + error_recieved;
	}
	try {
		load_until(L"L");
		load_until(L"{");
		do {
			l_names.push_back(load_until(L",}"));
		} while (last_char != '}');
	}
	catch (std::wstring error_recieved) {
		throw L"ERROR : Failed to load last names\n" + error_recieved;
	}
}
effect person::load_trait(std::wifstream& file, wchar_t& last_char) { //Loads trait from file
	effect temp_effect;
	try {
		std::wstring current_text; //Text currently read
		auto load_until = [&](std::wstring chars) { return search_until(file, chars, last_char); };
		auto load_string = [&]() { return load_quotes(file, last_char); };
		temp_effect.name = load_string();
		load_until(L",");
		temp_effect.description = load_string();
		load_until(L",");
		try {
			current_text = load_until(L",");
			temp_effect.diplomacy = stoi(current_text);
		}
		catch (...) {
			throw L"ERROR : Cannot Assign Diplomacy \"" + current_text + L"\" could not be assigned.";
		}
		try {
			current_text = load_until(L",");
			temp_effect.intrigue = stoi(current_text);
		}
		catch (...) {
			throw L"ERROR : Cannot Assign Intrigue \"" + current_text + L"\" could not be assigned.";
		}
		try {
			current_text = load_until(L",");
			temp_effect.appeal = stoi(current_text);
		}
		catch (...) {
			throw L"ERROR : Cannot Assign Appeal \"" + current_text + L"\" could not be assigned.";
		}
		try {
			current_text = load_until(L",");
			temp_effect.command = stoi(current_text);
		}
		catch (...) {
			throw L"ERROR : Cannot Assign Command \"" + current_text + L"\" could not be assigned.";
		}
		load_until(L"[");
		do {
			current_text = load_string();
			temp_effect.negative_traits.push_back(current_text);
			load_until(L",]");
		} while (last_char != ']');
		load_until(L",}");
	}
	catch (std::wstring error_recieved) {
		throw L"Failed to load trait\n" + error_recieved + L"\nName : L" + temp_effect.name + L"\nDesc : L" + temp_effect.description + L"\nDiplomacy : L" + std::to_wstring(temp_effect.diplomacy) + L"\nIntrigue : L" + std::to_wstring(temp_effect.intrigue) + L"\nAppeal : L" + std::to_wstring(temp_effect.appeal) + L"\nCommand : L" + std::to_wstring(temp_effect.command);
	}
	return temp_effect;
}
std::wostream &operator<<(std::wostream& os, effect const &temp_effect) {
	return os << L"\nName : L" + temp_effect.name << L"\nDesc : L" + temp_effect.description << L"\nDiplomacy : L" << std::to_wstring(temp_effect.diplomacy) << L"\nIntrigue : L" << std::to_wstring(temp_effect.intrigue) << L"\nAppeal : L" << std::to_wstring(temp_effect.appeal) << L"\nCommand : L" << std::to_wstring(temp_effect.command);
}
map::coord::coord() {};
map::coord::~coord() {};
map::state::state(int p_id, std::wstring p_name) {
	clique_id = p_id;
	name = p_name;
}
map::state::state(int p_id) {
	clique_id = p_id;
}
map::state::~state() {}
const auto& map::state::get_neighbors() {
	return neighbors;
}
map::state map::load_state(std::wifstream& file, wchar_t& last_char) { //Load a singular state
	auto load_until = [&](std::wstring chars) { return search_until(file, chars, last_char); };
	auto load_string = [&]() { return load_quotes(file, last_char); };
	std::wstring current_text; //current text read
	state temp_state(0);
	try {//Loading in name
		current_text = load_string();
		temp_state.name = current_text;
	}
	catch (std::wstring error_recieved) {
		throw L"ERROR : Failed to load state\n" + error_recieved + L"\n" + current_text;
	}
	try {//Loading neighbors
		load_until(L"-");
		do {
			temp_state.neighbors.push_back(load_string());
			load_until(L",-");
		} while (last_char != '-');
	}
	catch (std::wstring error_recieved) {
		throw L"ERROR : Failed to find neighbors when loading state : L" + error_recieved + L"\n" + temp_state.name;
	}
	try { //Loading Pixels
		load_until(L"{");
		do {
			coord temp_coord;
			current_text = load_until(L",");
			temp_coord.x = stoi(current_text);
			current_text = load_until(L",}");
			temp_coord.y = stoi(current_text);
			temp_state.pixels.push_back(temp_coord);
		} while (last_char != '}');

	}
	catch (std::wstring error_recieved) {
		throw L"ERROR : Failed to load pixels \n" + error_recieved;
	}
	load_until(L"-}");
	return temp_state;
}
void map::load_map_files() { //Loads in the map_display and the states information within the map
	std::wifstream map_file(L"USA.txt");
	wchar_t last_char; //Last character found
	auto load_until = [&](std::wstring chars) { return search_until(map_file, chars, last_char); };
	auto load_string = [&]() { return load_quotes(map_file, last_char); };
	try {
		load_until(L"M");
		load_until(L"{");
		display = load_until(L"}");
	}
	catch (std::wstring exp) {
		throw L"ERROR : Failed to read display for map_file\n" + exp + L"\nData Read : " + display;
	}
	load_until(L"D");
	load_until(L"{");
	while (last_char != '}') {
		states.push_back(load_state(map_file, last_char));
	}
}
void map::render_state(std::wstring wstr, wchar_t chr, WORD color) {
	for (auto state : states)
		if (state.name == wstr) {
			set_color(color);
			for (auto pixel : state.pixels) {
				set_pos((SHORT)pixel.x, (SHORT)pixel.y);
				std::wcout << chr;
			}
		}
}