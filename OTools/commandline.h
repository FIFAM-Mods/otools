#pragma once
#include <string>
#include <map>
#include <set>

class CommandLine {
    std::set<std::string> mOptions;
    std::map<std::string, std::string> mArguments;
public:
    CommandLine(int argc, char *argv[], std::set<std::string> const &arguments, std::set<std::string> const &options);
    bool HasOption(std::string const &option);
    bool HasArgument(std::string const &argument);
    std::string GetArgumentString(std::string const &argument, std::string const &defaultValue = std::string());
    int GetArgumentInt(std::string const &argument, int defaultValue = -1);
    float GetArgumentFloat(std::string const &argument, float defaultValue = 0.0f);
};
