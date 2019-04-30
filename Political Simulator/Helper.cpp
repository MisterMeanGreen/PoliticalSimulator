#pragma once
#include "Helper.h"
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
wchar_t wget(std::wifstream& file) {
	char bit1;
	char bit2;
	try {
		bit2 = static_cast<char>(file.get());
		bit1 = static_cast<char>(file.get());
	}
	catch (...) {
		throw L"Error reading bit.";
	}
	return ((bit1 << 8) | (bit2 & 0xff));
}
std::wstring search_until(std::wifstream& file, std::wstring chars, wchar_t& last_char) {
	std::wstring text;
	while (!file.eof()) {
		last_char = (text += wget(file)).back();
		for (auto c : chars)
			if (text.back() == c)
				goto found_char;
	}
	throw L"ERROR : Ending characters (" + chars + L") not found when reading \"" + text + L"\".";
found_char:
	return text.substr(0, text.size() - 1);
}
std::wstring load_quotes(std::wifstream& file, wchar_t& last_char) { //Locates and reads in everything between quotes
	std::wstring text;
	while (!file.eof())
		if ((last_char = (text += wget(file)).back()) == '"')
			goto found_beg_quote;
	throw L"ERROR : Start of string not found when reading \"" + text + L"\".";
found_beg_quote:
	text = L"";
	while (!file.eof())
		if ((last_char = (text += wget(file)).back()) == '"')
			goto found_end_quote;
	throw L"ERROR : End of string not found when reading \"" + text + L"\".";
found_end_quote:
	return text.substr(0, text.size() - 1);
};
BOOL set_color(WORD color) {
	return SetConsoleTextAttribute(hConsole, color);
}
BOOL set_pos(SHORT x, SHORT y) {
	return SetConsoleCursorPosition(hConsole, { x,y });
}
