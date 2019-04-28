#pragma once
#include <vector>
#include <utility>
#include <string>
#include <array>
#include <random>
#include <math.h>
#include <fstream>
#include <string>
#include <memory>
std::random_device rand_dev;
std::default_random_engine gen(rand_dev());
std::uniform_int_distribution<int> dist(0,99);
using namespace std;

enum pol_genders
{
	Male = 0, Female = 1
};
enum pol_stat_ids {
	diplomacy = 0, intrigue = 1, appeal = 2, command = 3
};
class effect { //Used as traits
public:
	string name;
	string description;
	int diplomacy; //Ability for Person to work with other Politicians
	int intrigue; //Ability for Person to conduct spying and espioange
	int appeal; //Ability for person to appeal to the people
	int command; //Ability for Person to control others
	effect(string p_name,string p_desc,int p_diplo,int p_int,int p_app,int p_comm) {
		name = p_name;
		description = p_desc;
		diplomacy = p_diplo;
		intrigue = p_int;
		appeal = p_app;
		command = p_comm;
	}
	vector<string> negative_traits; //Defines traits that the current trait cannot be in conjunction with
	effect() {
		name = "NULL";
		description = "NULL";
		diplomacy = 0;
		intrigue = 0;
		appeal = 0;
		command = 0; //Debug values to easily tell what values have been set when debugging
	}
	~effect() {}
	bool operator==(effect x) {
		return name == x.name;
	}
	bool operator!=(effect x) {
		return name != x.name;
	}
	bool contains_ntrait(string s) {
		for (auto x : negative_traits)
			if (x == s)
				return true;
		return false;
	}
};
vector<effect> traits;
vector<string> m_names;
vector<string> f_names;
vector<string> l_names;

#include <algorithm> //For finding objects in vectors
class person {
	string first_name; //Usually Random
	string last_name; //Dynastys!
	uint32_t age; //Age
	bool gender; //Gender
	int money; //Moolah
	vector<effect> traits; //Traits affect stats and other things
	int diplomacy; //Ability for Person to work with other Politicians
	int intrigue; //Ability for Person to conduct spying and espioange
	int appeal; //Ability for person to appeal to the people
	int command; //Ability for Person to control others
	uint32_t id;
	static uint32_t pub_id;
public:
	bool remove_trait(uint16_t trait_num) {//Removes a Single Trait as Postion X
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
	bool remove_trait(string name) { //Remove trait via name
		auto trait_itt = traits.begin();
		uint16_t trait_num = 0;
		while (trait_itt->name != name && trait_num < (traits.size()-1)) {
			trait_itt++;
			trait_num++;
		}
		return remove_trait(trait_num);
	}
	bool remove_trait(effect trait) { //Remove trait via another trait
		return remove_trait(trait.name);
	}
	void add_trait(effect trait){ //Add a single trait
		traits.push_back(trait);
		diplomacy += traits.back().diplomacy;
		intrigue += traits.back().intrigue;
		appeal += traits.back().appeal;
		command += traits.back().command;
	}
	void generate_random_traits() {//Generates Randomized Traits

	}
	void clear_traits() {
		while (!traits.empty()) {
			diplomacy -= traits.back().diplomacy;
			intrigue -= traits.back().intrigue;
			appeal -= traits.back().appeal;
			command -= traits.back().command;
			traits.pop_back();
		}
	}
	int add_stat(uint8_t stat, int amount) { //Change a one of the stats by amount
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
	}
	int get_stat(uint8_t stat) {
		switch (stat) {
		case pol_stat_ids::diplomacy:
			return (diplomacy + abs(diplomacy))/2;
		case pol_stat_ids::intrigue:
			return (intrigue + abs(intrigue)) / 2;
		case pol_stat_ids::appeal:
			return (appeal + abs(appeal)) / 2;
		case pol_stat_ids::command:
			return (command + abs(command)) / 2;
		}
		return -1;
	}
	string get_first_name() { return first_name; }
	string get_last_name() { return last_name; }
	string get_name() { return get_first_name() + ' ' + get_last_name(); }
	int add_money(int amount) { return money += amount; }
	int get_money() { return money; }
	int get_age() { return age; }
	uint32_t get_id() { return id; }
	string get_gender() { return (gender == pol_genders::Male ? "male" : "female"); }
	auto& operator[](uint32_t c) { return traits[c]; }
	auto& trait_list() { return traits; }
	person(string p_first_name, string p_last_name, uint32_t p_age, bool p_gender, int p_money, int p_diplomacy, int p_intrigue, int p_appeal, int p_command) : id(++pub_id) {
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
	person(string p_first_name, string p_last_name, uint32_t p_age, bool p_gender, int p_money) : id(++pub_id) {
		first_name = p_first_name;
		last_name = p_last_name;
		age = p_age;
		gender = p_gender;
		money = p_money;
		diplomacy = 0;
		intrigue = 0;
		appeal = 0;
		command = 0;
		std::uniform_int_distribution<int> rand_stat(0, 3); //Random stat to upgrade
		std::uniform_int_distribution<int> rand_total(5, 25); //Random total amount you can upgrade
		auto total = rand_total(gen);
		for(auto x = 0;x< total;x++)
		switch (rand_stat(gen)) {
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
		generate_random_traits();
	} //Generate Random Traits and Stats
	person(uint32_t p_age, int p_money) : id(++pub_id) {
		age = p_age;
		gender = dist(gen) > 50;
		if (gender == pol_genders::Male) {
			uniform_int_distribution<int> ListSize(0, m_names.size() - 1);
			first_name = m_names[ListSize(gen)];

		}
		else {
			uniform_int_distribution<int> ListSize(0, f_names.size() - 1);
			first_name = f_names[ListSize(gen)];
		}
		uniform_int_distribution<int> ListSize(0, l_names.size() - 1);
		last_name = l_names[ListSize(gen)];
		money = p_money;
		diplomacy = 0;
		intrigue = 0;
		appeal = 0;
		command = 0;
		std::uniform_int_distribution<int> rand_stat(0, 3); //Random stat to upgrade
		std::uniform_int_distribution<int> rand_total(5, 25); //Random total amount you can upgrade
		auto total = rand_total(gen);
		for (auto x = 0; x< total; x++)
			switch (rand_stat(gen)) {
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
		generate_random_traits();
	} //Generate Random Traits and Stats
	person(uint32_t p_age) : id(++pub_id) {
		age = p_age;
		gender = dist(gen) < 50;
		if (gender == pol_genders::Male) {
			uniform_int_distribution<int> ListSize(0, m_names.size() - 1);
			first_name = m_names[ListSize(gen)];

		}
		else {
			uniform_int_distribution<int> ListSize(0, f_names.size() - 1);
			first_name = f_names[ListSize(gen)];
		}
		uniform_int_distribution<int> ListSize(0, l_names.size() - 1);
		last_name = l_names[ListSize(gen)];
		money = ListSize(gen);
		diplomacy = 0;
		intrigue = 0;
		appeal = 0;
		command = 0;
		std::uniform_int_distribution<int> rand_stat(0, 3); //Random stat to upgrade
		std::uniform_int_distribution<int> rand_total(5, 25); //Random total amount you can upgrade
		auto total = rand_total(gen);
		for (auto x = 0; x< total; x++)
			switch (rand_stat(gen)) {
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
		generate_random_traits();
	} //Generate Random Traits and Stats
	person() : id(++pub_id) {
		uniform_int_distribution<int> age_gen(16, 80);
		age = age_gen(gen);
		gender = dist(gen) > 50;
		if (gender == pol_genders::Male) {
			uniform_int_distribution<int> ListSize(0, m_names.size() - 1);
			first_name = m_names[ListSize(gen)];

		}
		else {
			uniform_int_distribution<int> ListSize(0, f_names.size() - 1);
			first_name = f_names[ListSize(gen)];
		}
		uniform_int_distribution<int> ListSize(0, l_names.size() - 1);
		last_name = l_names[ListSize(gen)];
		money = ListSize(gen);
		diplomacy = 0;
		intrigue = 0;
		appeal = 0;
		command = 0;
		std::uniform_int_distribution<int> rand_stat(0, 3); //Random stat to upgrade
		std::uniform_int_distribution<int> rand_total(5, 25); //Random total amount you can upgrade
		auto total = rand_total(gen);
		for (auto x = 0; x< total; x++)
			switch (rand_stat(gen)) {
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
		generate_random_traits();
	} //Generate Random Traits and Stats
	static void load_player_files() { //Loads traits file, names for both females and males, and the last names
		ifstream file("traits.txt");
		string currently_parsed;
		while (!file.eof()) { //Load traits
			::traits.push_back(person::load_trait(file));
			file.get();
		}
		file.close();
		file.open("male_names.txt", fstream::in); //Load names
		while (file.peek() != EOF) {
			getline(file, currently_parsed);
			m_names.push_back(currently_parsed);
		}
		file.close();
		file.open("female_names.txt", fstream::in);
		while (file.peek() != EOF) {
			getline(file, currently_parsed);
			f_names.push_back(currently_parsed);
		}
		file.close();
		file.open("last_names.txt", fstream::in);
		while (file.peek() != EOF) {
			getline(file, currently_parsed);
			l_names.push_back(currently_parsed);
		}
	}
	static effect load_trait(ifstream& file) {
		auto load_string = [&]()->string { //Locates and reads in everything between quotes
			string text;
			while (!file.eof())
				if ((text += file.get()).at(text.size() - 1) == '"')
					goto found_beg_quote;
			throw "ERROR : Start of string not found when reading \"" + text + "\".";
		found_beg_quote:
			text = "";
			while (!file.eof())
				if ((text += file.get()).at(text.size() - 1) == '"')
					goto found_end_quote;
			throw "ERROR : End of string not found when reading \"" + text + "\".";
		found_end_quote:
			return text.substr(0, text.size() - 1);
		};
		auto load_until = [&](string chars)->string {
			string text;
			while (!file.eof()) {
				text += file.get();
				for (auto c : chars)
					if (text.at(text.size() - 1) == c)
						goto found_char;
			}
			throw "ERROR : Ending characters (" + chars + ") not found when reading \"" + text + "\".";
		found_char:
			return text.substr(0, text.size() - 1);
		};
		auto load_until_lchar = [&](string chars, char& last_char)->string {
			string text;
			while (!file.eof()) {
				text += file.get();
				for (auto c : chars)
					if (text.at(text.size() - 1) == c)
						goto found_char;
			}
			throw "ERROR : Ending characters (" + chars + ") not found when reading \"" + text + "\".";
		found_char:
			last_char = text.at(text.size() - 1);
			return text.substr(0, text.size() - 1);
		};
		effect temp_effect;
		try {
			string err; //temporary string
			char last_char;
			temp_effect.name = load_string();
			load_until(",");
			temp_effect.description = load_string();
			load_until(",");
			try {
				err = load_until(",");
				temp_effect.diplomacy = stoi(err);
			}
			catch (...) {
				throw "ERROR : Cannot Assign Diplomacy \"" + err + "\" could not be assigned.";
			}
			try {
				err = load_until(",");
				temp_effect.intrigue = stoi(err);
			}
			catch (...) {
				throw "ERROR : Cannot Assign Intrigue \"" + err + "\" could not be assigned.";
			}
			try {
				err = load_until(",");
				temp_effect.appeal = stoi(err);
			}
			catch (...) {
				throw "ERROR : Cannot Assign Appeal \"" + err + "\" could not be assigned.";
			}
			try {
				err = load_until_lchar(",", last_char);
				temp_effect.command = stoi(err);
			}
			catch (...) {
				throw "ERROR : Cannot Assign Command \"" + err + "\" could not be assigned.";
			}
			load_until("[");
				do {
					err = load_string();
					temp_effect.negative_traits.push_back(err);
					load_until_lchar(",]", last_char);
				} while (last_char != ']');
			}
		catch (string exp) {
			throw "Failed to load trait\n" + exp + "\nName : " + temp_effect.name + "\nDesc : " + temp_effect.description + "\nDiplomacy : " + to_string(temp_effect.diplomacy) + "\nIntrigue : " + to_string(temp_effect.intrigue) + "\nAppeal : " + to_string(temp_effect.appeal) + "\nCommand : " + to_string(temp_effect.command);
		}
		return temp_effect;
	}

};
std::ostream &operator<<(std::ostream &os, effect const &m) {
	return os << "Name : " << m.name << "\nDesc : " << m.description << "\nDiplomacy : " << m.diplomacy << "\nIntrigue : " << m.intrigue << "\nAppeal : " << m.appeal << "\nCommand : " << m.command;
}

class Map {
	struct coord { int x; int y; };
private:
	class state {
		//vector< coord > pixels TODO;

	public:
		int population;
		int income;
		vector<string> neighbors;
		int clique_id; //current clique id controlling it
		string name; //name of state
		state(int p_id, string p_name){
			clique_id = p_id;
			name = p_name;
		}
		state(int p_id) {
			clique_id = p_id;
		}
		~state() {}
		const auto& get_neighbors() {
			return neighbors;
		}
	};


public:
	wstring display;
	vector<state> states;
	state load_state(ifstream& file,char& lst_chr) {
		char last_char;
		auto load_string = [&]()->string { //Locates and reads in everything between quotes
			string text;
			while (!file.eof())
				if ((text += file.get()).at(text.size() - 1) == '"')
					goto found_beg_quote;
			throw "ERROR : Start of string not found when reading \"" + text + "\".";
		found_beg_quote:
			text = "";
			while (!file.eof())
				if ((text += file.get()).at(text.size() - 1) == '"')
					goto found_end_quote;
			throw "ERROR : End of string not found when reading \"" + text + "\".";
		found_end_quote:
			return text.substr(0, text.size() - 1);
		};
		auto load_until_lchar = [&](string chars)->string {
			string text;
			while (!file.eof()) {
				text += file.get();
				for (auto c : chars)
					if (text.at(text.size() - 1) == c)
						goto found_char;
			}
			throw "ERROR : Ending characters (" + chars + ") not found when reading \"" + text + "\".";
		found_char:
			last_char = text.at(text.size() - 1);
			return text.substr(0, text.size() - 1);
		};
		string text; //current text read
		state temp_state(0);
		try {//Loading in name
			text = load_string();
			temp_state.name = text;
		}
		catch (string err) {
			throw "ERROR : Failed to load state\n" + err + "\n" + text;
		}
		try {//Loading neighbors
			load_until_lchar("-");
			do {
				temp_state.neighbors.push_back(load_string());
				load_until_lchar(",-}");
			} while (last_char != '-' && last_char != '}');
		}
		catch (string err) {
			throw "ERROR : Failed to find neighbors when loading state : " + temp_state.name + "\n" + err;
		}
		lst_chr = last_char;
		return temp_state;
	}
	void load_map_files() { //Loads in the map_display and the states information within the map
		ifstream map_file("USA.txt");
		char last_char; //Last character found
		auto load_until_lchar = [&](string chars)->string {
			string text;
			while (!map_file.eof()) {
				text += map_file.get();
				for (auto c : chars)
					if (text.at(text.size() - 1) == c)
						goto found_char;
			}
			throw "ERROR : Ending characters (" + chars + ") not found when reading \"" + text + "\".";
		found_char:
			last_char = text.at(text.size() - 1);
			return text.substr(0, text.size() - 1);
		};
		auto wload_until_lchar = [&](wstring chars)->wstring {
			wstring text;
			while (!map_file.eof()) {
				char bit1 = map_file.get();
				char bit2 = map_file.get();
				text += ((bit2 << 8) | (bit1 & 0xff));
				for (auto c : chars)
					if (text.at(text.size() - 1) == c)
						goto found_char;
			}
			throw "ERROR : UNICODE ERROR";
		found_char:
			last_char = text.at(text.size() - 1);
			return text.substr(0, text.size() - 1);
		};
		try {
			wload_until_lchar(L"M");
			wload_until_lchar(L"{");
			display = wload_until_lchar(L"}");
		}
		catch (string exp) {
			throw "ERROR : Failed to read display for map_file\n" + exp;
		}
		map_file.close();
		map_file.open("USA_states.txt");
		load_until_lchar("D");
		load_until_lchar("{");
		while (last_char != '}') {
			states.push_back(load_state(map_file,last_char));
		}
	}
};
