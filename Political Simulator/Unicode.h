#pragma once
//Magic S*#! to make wcout, and wcin to work
#include <iostream>
#include <locale>
#include <locale.h>
#include <stdlib.h>

#ifndef MS_STDLIB_BUGS // Allow overriding the autodetection.
/* The Microsoft C and C++ runtime libraries that ship with Visual Studio, as
* of 2017, have a bug that neither stdio, iostreams or wide iostreams can
* handle Unicode input or output.  Windows needs some non-standard magic to
* work around that.  This includes programs compiled with MinGW and Clang
* for the win32 and win64 targets.
*/
#  if ( _MSC_VER || __MINGW32__ || __MSVCRT__ )
/* This code is being compiled either on MS Visual C++, or MinGW, or
* clang++ in compatibility mode for either, or is being linked to the
* msvcrt.dll runtime.
*/
#    define MS_STDLIB_BUGS 1
#  else
#    define MS_STDLIB_BUGS 0
#  endif
#endif

#if MS_STDLIB_BUGS
#  include <io.h>
#  include <fcntl.h>
#endif

#if !HAS_APP17_FILESYSTEM && !HAS_TS_FILESYSTEM && __has_include(<filesystem>)
#  include <filesystem> /* MSVC has this header, but not the standard API. */
#  if __cpp_lib_filesystem >= 201703
#    define HAS_CPP17_FILESYSTEM 1
#  endif
#endif

#if !HAS_CPP17_FILESYSTEM && __has_include(<experimental/filesystem>)
#  include <experimental/filesystem>
/* Microsoft screws this one up, too, by not defining the feature-test
* macro specified by the standard.
*/
#  if __cpp_lib_experimental_filesystem >= 201406 || MS_STDLIB_BUGS
#    define HAS_TS_FILESYSTEM 1
/* With g++6, this requires -lstdc++fs, AFTER this source file on the
* command line.
*/
#  endif
#endif

#if HAS_CPP17_FILESYSTEM
using std::filesystem::absolute;
using std::filesystem::current_path;
using std::filesystem::directory_entry;
using std::filesystem::directory_iterator;
using std::filesystem::is_directory;
using std::filesystem::exists;
using std::filesystem::path;
#elif HAS_TS_FILESYSTEM
using std::experimental::filesystem::absolute;
using std::experimental::filesystem::current_path;
using std::experimental::filesystem::directory_entry;
using std::experimental::filesystem::directory_iterator;
using std::experimental::filesystem::is_directory;
using std::experimental::filesystem::exists;
using std::experimental::filesystem::path;
#else
#  error "This library has neither <filesystem> nor <experimental/filesystem>."
#endif

void init_locale(void);