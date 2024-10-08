#ifndef __SEXYAPPFRAMEWORK_COMMON_H__
#define __SEXYAPPFRAMEWORK_COMMON_H__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdint>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <cwctype>
#include <execution>
#include <fmt/core.h>
#include <list>
#include <map>
#include <mutex>
#include <optional>
#include <set>
#include <string>
#include <todlib/TodDebug.h>
#include <vector>

#ifndef __cpp_lib_unreachable
[[noreturn]] inline void unreachable() {
    #if defined(_MSC_VER) && !defined(__clang__) // MSVC
        __assume(false);
    #else
        // If not using MSVC, define unreachable as a no-op
        do {} while(0);
    #endif
}
#endif // __cpp_lib_unreachable

#ifdef _MSC_VER
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#else
#define unreachable do {} while(0)
#endif

#define _MAX_PATH 260

// Removed wide string support
using SexyString = std::string;
#define _S(x) x

#define SexyStringToStringFast(x) (x)
#define SexyStringToWStringFast(x) StringToWString(x)
#define StringToSexyStringFast(x) (x)
#define WStringToSexyStringFast(x) WStringToString(x)

#define LONG_BIGE_TO_NATIVE(l)                                                                                         \
    (((l >> 24) & 0xFF) | ((l >> 8) & 0xFF00) | ((l << 8) & 0xFF0000) | ((l << 24) & 0xFF000000))
#define WORD_BIGE_TO_NATIVE(w) (((w >> 8) & 0xFF) | ((w << 8) & 0xFF00))
#define LONG_LITTLEE_TO_NATIVE(l) (l)
#define WORD_LITTLEE_TO_NATIVE(w) (w)

#ifndef _MSC_VER
typedef unsigned char BYTE;
typedef uint16_t WORD;
typedef unsigned int DWORD;
typedef int LONG;
typedef unsigned int UINT;
#else
#define NOMINMAX 1
#include <intsafe.h>
#if alloca == _alloca
#undef alloca
#define alloca _malloca
#endif // alloca == _alloca
#endif // _MSC_VER

using DefinesMap = std::map<std::string, std::string>;
using WStringWStringMap = std::map<std::wstring, std::wstring>;
using SexyChar = SexyString::value_type;

#define HAS_SEXYCHAR

namespace Sexy {
constexpr uint32_t SEXY_RAND_MAX = 0x7FFFFFFF;

extern bool gDebug;

int Rand();
int Rand(int range);
float Rand(float range);
void SRand(uint32_t theSeed);
// extern std::string vformat(const char *fmt, va_list argPtr);
// extern std::wstring vformat(const wchar_t *fmt, va_list argPtr);
// extern std::string StrFormat(const char *fmt...);
// extern std::wstring StrFormat(const wchar_t *fmt...);
bool CheckFor98Mill();
bool CheckForVista();
std::string GetAppDataFolder();
void SetAppDataFolder(const std::string &thePath);
std::string URLEncode(const std::string &theString);
std::string StringToUpper(const std::string &theString);
std::wstring StringToUpper(const std::wstring &theString);
std::string StringToLower(const std::string &theString);
std::wstring StringToLower(const std::wstring &theString);
std::wstring StringToWString(const std::string &theString);
std::string WStringToString(const std::wstring &theString);
SexyString StringToSexyString(const std::string &theString);
SexyString WStringToSexyString(const std::wstring &theString);
std::string SexyStringToString(const SexyString &theString);
std::wstring SexyStringToWString(const SexyString &theString);
std::string Upper(const std::string &theData);
std::wstring Upper(const std::wstring &theData);
std::string Lower(const std::string &theData);
std::wstring Lower(const std::wstring &theData);
std::string Trim(const std::string &theString);
std::wstring Trim(const std::wstring &theString);
bool StringToInt(const std::string &theString, int *theIntVal);
bool StringToDouble(const std::string &theString, double *theDoubleVal);
bool StringToInt(const std::wstring &theString, int *theIntVal);
bool StringToDouble(const std::wstring &theString, double *theDoubleVal);
int StrFindNoCase(const char *theStr, const char *theFind);
bool StrPrefixNoCase(const char *theStr, const char *thePrefix, int maxLength = 10000000);
SexyString CommaSeperate(int theValue);
std::string Evaluate(const std::string &theString, const DefinesMap &theDefinesMap);
std::string XMLDecodeString(const std::string &theString);
std::string XMLEncodeString(const std::string &theString);
std::wstring XMLDecodeString(const std::wstring &theString);
std::wstring XMLEncodeString(const std::wstring &theString);

bool Deltree(const std::string &thePath);
bool FileExists(const std::string &theFileName);
void MkDir(const std::string &theDir);
std::string GetFileName(const std::string &thePath, bool noExtension = false);
std::string GetFileDir(const std::string &thePath, bool withSlash = false);
std::string RemoveTrailingSlash(const std::string &theDirectory);
std::string AddTrailingSlash(const std::string &theDirectory, bool backSlash = false);
time_t GetFileDate(const std::string &theFileName);
std::string GetCurDir();
std::string GetFullPath(const std::string &theRelPath);
std::string GetPathFrom(const std::string &theRelPath, const std::string &theDir);
bool AllowAllAccess(const std::string &theFileName);
std::wstring UTF8StringToWString(const std::string &theString);

// Read memory and then move the pointer
void SMemR(void *&_Src, void *_Dst, size_t _Size);
void SMemRStr(void *&_Src, std::string &theString);
// Write memory and then move the pointer
void SMemW(void *&_Dst, const void *_Src, size_t _Size);
void SMemWStr(void *&_Dst, const std::string &theString);

inline void inlineUpper(std::string &theData) {
    // std::transform(theData.begin(), theData.end(), theData.begin(), toupper);

    int aStrLen = static_cast<int>(theData.length());
    for (int i = 0; i < aStrLen; i++) {
        theData[i] = toupper(theData[i]);
    }
}

inline void inlineUpper(std::wstring &theData) {
    // std::transform(theData.begin(), theData.end(), theData.begin(), toupper);

    int aStrLen = static_cast<int>(theData.length());
    for (int i = 0; i < aStrLen; i++) {
        theData[i] = std::towupper(theData[i]);
    }
}

inline void inlineLower(std::string &theData) {
    std::transform(theData.begin(), theData.end(), theData.begin(), tolower);
}

inline void inlineLower(std::wstring &theData) {
    std::transform(theData.begin(), theData.end(), theData.begin(), tolower);
}

inline void inlineLTrim(std::string &theData, const std::string &theChars = " \t\r\n") {
    theData.erase(0, theData.find_first_not_of(theChars));
}

inline void inlineLTrim(std::wstring &theData, const std::wstring &theChars = L" \t\r\n") {
    theData.erase(0, theData.find_first_not_of(theChars));
}

inline void inlineRTrim(std::string &theData, const std::string &theChars = " \t\r\n") {
    theData.resize(theData.find_last_not_of(theChars) + 1);
}

inline void inlineTrim(std::string &theData, const std::string &theChars = " \t\r\n") {
    inlineRTrim(theData, theChars);
    inlineLTrim(theData, theChars);
}

struct StringLessNoCase {
    bool operator()(const std::string &s1, const std::string &s2) const {
        return strcasecmp(s1.c_str(), s2.c_str()) < 0;
    }
};
} // namespace Sexy

#endif //__SEXYAPPFRAMEWORK_COMMON_H__
