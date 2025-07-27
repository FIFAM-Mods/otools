#pragma once
#include <exception>
#include <string>

namespace ea {

	class Exception : public std::exception {
		std::string mMessage;
	public:
		Exception(std::string const &message);
		char const *what() const noexcept override;
	};

}
