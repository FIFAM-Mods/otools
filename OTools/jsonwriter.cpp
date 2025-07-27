#include "jsonwriter.h"
#include "outils.h"
#include <fstream>

JsonWriter::JsonWriter(path const &outputPath) {
    mResult.clear();
    mOutputPath = outputPath;
    mCurrentSpacing = 0;
    mJustOpened = false;
    mJustClosed = false;
}

JsonWriter::~JsonWriter() {
    close();
}

string JsonWriter::spacing() {
    if (mCurrentSpacing > 0)
        return string(mCurrentSpacing * 4, L' ');
    return string();
}

void JsonWriter::startScope() {
    mResult.clear();
    mCurrentSpacing = 0;
    mJustOpened = true;
    mJustClosed = false;
    mResult += "{";
    mCurrentSpacing++;
}

void JsonWriter::endScope() {
    mResult += "\n}\n";
}

void JsonWriter::openScope(string const &title) {
    if (!mJustOpened)
        mResult += ",";
    mResult += "\n" + spacing();
    if (!title.empty())
        mResult += "\"" + title + "\" : ";
    mResult += "{";
    mJustOpened = true;
    mCurrentSpacing++;
}

void JsonWriter::openArray(string const &title) {
    if (!mJustOpened)
        mResult += ",";
    mResult += "\n" + spacing();
    if (!title.empty())
        mResult += "\"" + title + "\" : ";
    mResult += "[";
    mJustOpened = true;
    mCurrentSpacing++;
}

void JsonWriter::closeScope(bool isLast) {
    mJustOpened = false;
    mCurrentSpacing--;
    mResult += "\n" + spacing() + "}";
}

void JsonWriter::closeArray(bool isLast) {
    mJustOpened = false;
    mCurrentSpacing--;
    mResult += "\n" + spacing() + "]";
}

void JsonWriter::writeValueString(string const &value) {
    mResult += (mJustOpened ? "\n" : ",\n") + spacing() + "\"" + value + "\"";
    mJustOpened = false;
}

void JsonWriter::writeValueInt(int value) {
    mResult += (mJustOpened ? "\n" : ",\n") + spacing() + to_string(value);
    mJustOpened = false;
}

void JsonWriter::writeValueFloat(float value) {
    mResult += (mJustOpened ? "\n" : ",\n") + spacing() + Format("%.15g", value);
    mJustOpened = false;
}

void JsonWriter::writeValueDouble(double value) {
    mResult += (mJustOpened ? "\n" : ",\n") + spacing() + to_string(value);
    mJustOpened = false;
}

void JsonWriter::writeValuebool(bool value) {
    mResult += (mJustOpened ? "\n" : ",\n") + spacing() + (value ? "true" : "false");
    mJustOpened = false;
}

void JsonWriter::writeFieldString(string const &name, string const &value) {
    mResult += (mJustOpened ? "\n" : ",\n") + spacing() + "\"" + name + "\" : \"" + value + "\"";
    mJustOpened = false;
}

void JsonWriter::writeFieldInt(string const &name, int value) {
    mResult += (mJustOpened ? "\n" : ",\n") + spacing() + "\"" + name + "\" : " + to_string(value);
    mJustOpened = false;
}

void JsonWriter::writeFieldFloat(string const &name, float value) {
    mResult += (mJustOpened ? "\n" : ",\n") + spacing() + "\"" + name + "\" : " + Format("%.15g", value);
    mJustOpened = false;
}

void JsonWriter::writeFieldDouble(string const &name, double value) {
    mResult += (mJustOpened ? "\n" : ",\n") + spacing() + "\"" + name + "\" : " + to_string(value);
    mJustOpened = false;
}

void JsonWriter::writeFieldBool(string const &name, bool value) {
    mResult += (mJustOpened ? "\n" : ",\n") + spacing() + "\"" + name + "\" : " + (value ? "true" : "false");
    mJustOpened = false;
}

string JsonWriter::base64_encode(unsigned char const *bytes_to_encode, unsigned int in_len) {
    static const string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    if (i) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];
        while ((i++ < 3))
            ret += '=';
    }
    return ret;
}

void JsonWriter::close() {
    if (!mOutputPath.empty()) {
        ofstream w(mOutputPath, ios::out);
        if (w.is_open())
            w << mResult;
    }
    mResult.clear();
    mOutputPath.clear();
}

string &JsonWriter::result() {
    return mResult;
}
