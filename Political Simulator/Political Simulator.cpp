// Political Simulator.cpp : Defines the entry point for the console application.
//Nicholas Dundas
//Game about controlling the USA
#include <Windows.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Standards.h"
#ifndef MS_STDLIB_BUGS
#  if ( _MSC_VER || __MINGW32__ || __MSVCRT__ )
#    define MS_STDLIB_BUGS 1
#  else
#    define MS_STDLIB_BUGS 0
#  endif
#endif

#if MS_STDLIB_BUGS
#  include <io.h>
#  include <fcntl.h>
#endif

void init_locale(void)
{
#if MS_STDLIB_BUGS
	constexpr char cp_utf16le[] = ".1200";
	setlocale(LC_ALL, cp_utf16le);
	_setmode(_fileno(stdout), _O_WTEXT);
#else
	// The correct locale name may vary by OS, e.g., "en_US.utf8".
	constexpr char locale_name[] = "";
	setlocale(LC_ALL, locale_name);
	std::locale::global(std::locale(locale_name));
	std::wcin.imbue(std::locale())
		std::wcout.imbue(std::locale());
#endif
}
using namespace std;



int main()
{
	Map USA;
	USA.load_map_files();
	person::load_player_files();
}

