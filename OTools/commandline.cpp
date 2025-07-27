#include "commandline.h"
#include "outils.h"

CommandLine::CommandLine(int argc, char *argv[], std::set<std::string> const &arguments, std::set<std::string> const &options) {
    std::set<std::string> _arguments;
    std::set<std::string> _options;
    for (auto const &s : arguments)
        _arguments.insert(ToLower(s));
    for (auto const &s : options)
        _options.insert(ToLower(s));
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg.starts_with('-')) {
            arg = ToLower(arg.substr(1));
            if (_arguments.contains(arg)) {
                if ((i + 1) < argc)
                    mArguments[arg] = argv[i + 1];
                else
                    break;
            }
            else if (_options.contains(arg))
                mOptions.insert(arg);
        }
    }
}

bool CommandLine::HasOption(std::string const &option) {
    return mOptions.contains(ToLower(option));
}

bool CommandLine::HasArgument(std::string const &argument) {
    return mArguments.contains(ToLower(argument));
}

std::string CommandLine::GetArgumentString(std::string const &argument, std::string const &defaultValue) {
    auto l = ToLower(argument);
    if (HasArgument(l))
        return mArguments[l];
    return defaultValue;
}

int CommandLine::GetArgumentInt(std::string const &argument, int defaultValue) {
    auto l = ToLower(argument);
    if (HasArgument(l)) {
        try {
            return std::stoi(mArguments[l]);
        }
        catch (...) {}
    }
    return defaultValue;
}

float CommandLine::GetArgumentFloat(std::string const &argument, float defaultValue) {
    auto l = ToLower(argument);
    if (HasArgument(l)) {
        try {
            return std::stof(mArguments[l]);
        }
        catch (...) {}
    }
    return defaultValue;
}
