#pragma once
#include <tchar.h>

#ifdef _DEBUG
#define DEBUG(fmt, ...) (_tprintf(_T(fmt), __VA_ARGS__))
#else
#define DEBUG(...) (0)
#endif

#ifndef FAKEDELETESUFFIX
#define FAKEDELETESUFFIX _T(".wanabak")
#endif // ! FAKEDELETESUFFIX
