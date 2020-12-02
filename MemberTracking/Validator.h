#pragma once
#include <string>

class ValidationException : public std::exception
{
	private:
		std::string errorMessage;

	public:
		ValidationException(std::string);
		const char* what();
};

class Validator
{
	public:
		void validateAge(std::string) const;
		void validateString(std::string) const;
		void validateStrings(std::string, std::string, std::string) const;
};