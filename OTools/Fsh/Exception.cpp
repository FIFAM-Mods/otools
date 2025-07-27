#include "Exception.h"

ea::Exception::Exception(std::string const & message) : mMessage(message) {}

char const *ea::Exception::what() const noexcept {
	return mMessage.c_str();
}
