#pragma once
#include <string>
#include <fstream>
std::string search_until(std::ifstream& file,std::string chars,char& last_char) {
	std::string text;
	while (!file.eof()) {
		last_char = (text += static_cast<char>(file.get())).back();
		for (auto c : chars)
			if (text.back() == c)
				goto found_char;
	}
	throw "ERROR : Ending characters (" + chars + ") not found when reading \"" + text + "\".";
found_char:
	return text.substr(0, text.size() - 1);
}
std::string load_quotes(std::ifstream& file,char& last_char) { //Locates and reads in everything between quotes
	std::string text;
	while (!file.eof())
		if ((last_char = (text += static_cast<char>(file.get())).back()) == '"')
			goto found_beg_quote;
	throw "ERROR : Start of string not found when reading \"" + text + "\".";
found_beg_quote:
	text = "";
	while (!file.eof())
		if ((last_char = (text += static_cast<char>(file.get())).back()) == '"')
			goto found_end_quote;
	throw "ERROR : End of string not found when reading \"" + text + "\".";
found_end_quote:
	return text.substr(0, text.size() - 1);
};