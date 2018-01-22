#ifndef SQAOD_COMMON_DEFINES_H__
#define SQAOD_COMMON_DEFINES_H__

#include <assert.h>


#ifdef __GNUC__
#define FORMATATTR(stringIdx, firstToCheck) __attribute__((format(printf, stringIdx, firstToCheck)))
#else
#define FORMATATTR(stringIdx, firstToCheck)
#endif


namespace sqaod {

typedef unsigned int SizeType;
typedef int IdxType;

void __abort(const char *file, unsigned long line);
void __abort(const char *file, unsigned long line, const char *format, ...) FORMATATTR(3, 4);

template <class... Args> inline
void _abort(const char *file, unsigned long line, Args... args) {
    __abort(file, line, args...);
}

void __throwError(const char *file, unsigned long line);
void __throwError(const char *file, unsigned long line, const char *format, ...) FORMATATTR(3, 4);

template <class... Args> inline
void _throwError(const char *file, unsigned long line, Args... args) {
    __throwError(file, line, args...);
}


}

/* FIXME: undef somewhere */
#define abort_(...) sqaod::_abort(__FILE__, __LINE__, __VA_ARGS__)
#define abortIf(cond, ...) if (cond) sqaod::_abort(__FILE__, __LINE__, __VA_ARGS__)
#define throwError(...) throw sqaod::_throwError(__FILE__, __LINE__, __VA_ARGS__)
#define throwErrorIf(cond, ...) if (cond) sqaod::_throwError(__FILE__, __LINE__, __VA_ARGS__)

#endif
