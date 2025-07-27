#pragma once
#include <string>
#include "outils.h"
#include <iostream>

enum MessageDisplayType {
    MSG_MESSAGE_BOX,
    MSG_CONSOLE,
    MSG_NONE
};

extern MessageDisplayType displayType;

void SetMessageDisplayType(MessageDisplayType type);
bool ErrorMessage(std::string const &msg);
bool InfoMessage(std::string const &msg);
