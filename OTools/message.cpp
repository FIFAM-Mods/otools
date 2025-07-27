#include "message.h"

MessageDisplayType displayType = MessageDisplayType::MSG_NONE;

void SetMessageDisplayType(MessageDisplayType type) {
    displayType = type;
}

void Message(std::string const &msg, bool error) {
    if (displayType == MessageDisplayType::MSG_MESSAGE_BOX) {
        Error(msg.c_str());
    }
    else if (displayType == MessageDisplayType::MSG_CONSOLE)
        std::cout << msg << std::endl;
}

bool ErrorMessage(std::string const &msg) {
    Message(msg, true);
    return false;
}

bool InfoMessage(std::string const &msg) {
    Message(msg, false);
    return true;
}
