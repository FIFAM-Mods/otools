#include "outils.h"
#include "WinInclude.h"

unsigned int FormattingUtils::currentBuf = 0;
char FormattingUtils::buf[FormattingUtils::BUF_SIZE][4096];
unsigned int FormattingUtils::currentBufW = 0;
wchar_t FormattingUtils::bufW[FormattingUtils::BUF_SIZE][4096];

std::wstring AtoW(std::string const &str) {
    std::wstring result;
    result.resize(str.size());
    for (unsigned int i = 0; i < str.size(); i++)
        result[i] = static_cast<wchar_t>(static_cast<unsigned char>(str[i]));
    return result;
}

std::string WtoA(std::wstring const &str) {
    std::string result;
    result.resize(str.size());
    for (unsigned int i = 0; i < str.size(); i++)
        result[i] = static_cast<char>(static_cast<unsigned char>(str[i]));
    return result;
}

std::string ToUpper(std::string const &str) {
    std::string result;
    for (size_t i = 0; i < str.length(); i++)
        result += toupper(static_cast<unsigned char>(str[i]));
    return result;
}

std::string ToLower(std::string const &str) {
    std::string result;
    for (size_t i = 0; i < str.length(); i++)
        result += tolower(static_cast<unsigned char>(str[i]));
    return result;
}

std::wstring ToUpper(std::wstring const &str) {
    std::wstring result;
    for (size_t i = 0; i < str.length(); i++)
        result += toupper(static_cast<unsigned short>(str[i]));
    return result;
}

std::wstring ToLower(std::wstring const &str) {
    std::wstring result;
    for (size_t i = 0; i < str.length(); i++)
        result += tolower(static_cast<unsigned short>(str[i]));
    return result;
}

void Replace(std::string &str, const std::string &from, const std::string &to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void Replace(std::wstring &str, const std::wstring &from, const std::wstring &to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void Trim(std::string &str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start != std::string::npos)
        str = str.substr(start);
    size_t end = str.find_last_not_of(" \t\r\n");
    if (end != std::string::npos)
        str = str.substr(0, end + 1);
}

void Trim(std::wstring &str) {
    size_t start = str.find_first_not_of(L" \t\r\n");
    if (start != std::wstring::npos)
        str = str.substr(start);
    size_t end = str.find_last_not_of(L" \t\r\n");
    if (end != std::wstring::npos)
        str = str.substr(0, end + 1);
}

std::vector<std::string> Split(std::string const &line, char delim, bool trim, bool skipEmpty, bool quotesHavePriority) {
    std::vector<std::string> result;
    std::string currStr;
    auto AddStr = [&, trim, skipEmpty]() {
        if (trim)
            Trim(currStr);
        if (!skipEmpty || !currStr.empty())
            result.push_back(currStr);
        currStr.clear();
    };
    bool inQuotes = false;
    for (size_t i = 0; i < line.length(); i++) {
        auto c = line[i];
        if (c == '\r' || (delim != '\n' && c == '\n'))
            break;
        if (!inQuotes) {
            if (quotesHavePriority && c == '"')
                inQuotes = true;
            else if (c == delim)
                AddStr();
            else
                currStr += c;
        }
        else {
            if (c == '"')
                inQuotes = false;
            else
                currStr += c;
        }
    }
    AddStr();
    return result;
}

std::vector<std::wstring> Split(std::wstring const &line, wchar_t delim, bool trim, bool skipEmpty, bool quotesHavePriority) {
    std::vector<std::wstring> result;
    std::wstring currStr;
    auto AddStr = [&, trim, skipEmpty]() {
        if (trim)
            Trim(currStr);
        if (!skipEmpty || !currStr.empty())
            result.push_back(currStr);
        currStr.clear();
    };
    bool inQuotes = false;
    for (size_t i = 0; i < line.length(); i++) {
        auto c = line[i];
        if (c == L'\r' || (delim != L'\n' && c == L'\n'))
            break;
        if (!inQuotes) {
            if (quotesHavePriority && c == L'"')
                inQuotes = true;
            else if (c == delim)
                AddStr();
            else
                currStr += c;
        }
        else {
            if (c == L'"')
                inQuotes = false;
            else
                currStr += c;
        }
    }
    AddStr();
    return result;
}

unsigned int Hash(std::string const &str) {
    unsigned int hash = 0;
    for (auto const &c : str) {
        hash += c;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

UINT MessageIcon(unsigned int iconType) {
    if (iconType == 1)
        return MB_ICONWARNING;
    else if (iconType == 2)
        return MB_ICONERROR;
    return MB_ICONINFORMATION;
}

void FormattingUtils::WindowsMessageBoxA(char const *msg, char const *title, unsigned int icon) {
    MessageBoxA(GetActiveWindow(), msg, title, MessageIcon(icon));
}

void FormattingUtils::WindowsMessageBoxW(wchar_t const *msg, wchar_t const *title, unsigned int icon) {
    MessageBoxW(GetActiveWindow(), msg, title, MessageIcon(icon));
}

char *FormattingUtils::GetBuf() {
    char *result = buf[currentBuf];
    currentBuf += 1;
    if (currentBuf >= BUF_SIZE)
        currentBuf = 0;
    return result;
}

wchar_t *FormattingUtils::GetBufW() {
    wchar_t *result = bufW[currentBufW];
    currentBufW += 1;
    if (currentBufW >= BUF_SIZE)
        currentBufW = 0;
    return result;
}

float SafeConvertFloat(std::wstring const &str) {
    float result = 0.0f;
    try {
        result = std::stof(str);
    }
    catch (...) {}
    return result;
}

float SafeConvertFloat(std::string const &str) {
    float result = 0.0f;
    try {
        result = std::stof(str);
    }
    catch (...) {}
    return result;
}

double SafeConvertDouble(std::wstring const &str) {
    double result = 0.0;
    try {
        result = std::stod(str);
    }
    catch (...) {}
    return result;
}

double SafeConvertDouble(std::string const &str) {
    double result = 0.0;
    try {
        result = std::stod(str);
    }
    catch (...) {}
    return result;
}

std::filesystem::path GetOToolsExePath() {
    static constexpr auto INITIAL_BUFFER_SIZE = MAX_PATH;
    static constexpr auto MAX_ITERATIONS = 7;
    std::wstring ret;
    auto bufferSize = INITIAL_BUFFER_SIZE;
    for (size_t iterations = 0; iterations < MAX_ITERATIONS; ++iterations) {
        ret.resize(bufferSize);
        auto charsReturned = GetModuleFileNameW(NULL, &ret[0], bufferSize);
        if (charsReturned < ret.length()) {
            ret.resize(charsReturned);
            return ret;
        }
        else
            bufferSize *= 2;
    }
    return std::filesystem::path();
}

std::filesystem::path GetOToolsDir() {
    auto exePath = GetOToolsExePath();
    if (exePath.has_parent_path())
        return exePath.parent_path();
    return std::filesystem::path();
}
