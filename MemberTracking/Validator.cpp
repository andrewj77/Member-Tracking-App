#include "Validator.h"

void Validator::validateAge(std::string age) const
{
	for (auto digit : age)
		if (!isdigit(digit))
			throw ValidationException("Invalid integer!\n");
}

void Validator::validateString(std::string someName) const
{
	if (someName == "")
		throw ValidationException("Empty string!\n");
}

void Validator::validateStrings(std::string first, std::string second, std::string third) const
{
	validateString(first);
	validateString(second);
	validateString(third);
}

ValidationException::ValidationException(std::string errorMessage)
{
	this->errorMessage = errorMessage;
}

const char* ValidationException::what()
{
	return this->errorMessage.c_str();
}