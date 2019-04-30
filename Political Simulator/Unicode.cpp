#pragma once
//Magic S*#! to make wcout, and wcin to work
#include "Unicode.h"

void init_locale(void)
// Does magic so that wcout can work.
{
#if MS_STDLIB_BUGS
	// Windows needs a little non-standard magic.
	constexpr char cp_utf16le[] = ".1200"; // UTF-16 little-endian locale.
	setlocale(LC_ALL, cp_utf16le);
	_setmode(_fileno(stdout), _O_WTEXT);
	/* Repeat for _fileno(stdin), if needed. */
#else
	// The correct locale name may vary by OS, e.g., "en_US.utf8".
	constexpr char locale_name[] = "";
	setlocale(LC_ALL, locale_name);
	std::locale::global(std::locale(locale_name));
	std::wcin.imbue(std::locale())
		std::wcout.imbue(std::locale());
#endif
}
