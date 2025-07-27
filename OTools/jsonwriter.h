#pragma once
#include <string>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

class JsonWriter {
    string mResult;
    path mOutputPath;
    unsigned int mCurrentSpacing = 0;
    bool mJustOpened = true;
    bool mJustClosed = false;
public:
    JsonWriter(path const &outputPath);
    ~JsonWriter();
    string spacing();
    void startScope();
    void endScope();
    void openScope(string const &title = string());
    void openArray(string const &title = string());
    void closeScope(bool isLast = false);
    void closeArray(bool isLast = false);
    void writeValueString(string const &value);
    void writeValueInt(int value);
    void writeValueFloat(float value);
    void writeValueDouble(double value);
    void writeValuebool(bool value);
    void writeFieldString(string const &name, string const &value);
    void writeFieldInt(string const &name, int value);
    void writeFieldFloat(string const &name, float value);
    void writeFieldDouble(string const &name, double value);
    void writeFieldBool(string const &name, bool value);
    static string base64_encode(unsigned char const *bytes_to_encode, unsigned int in_len);
    void close();
    string &result();
};
