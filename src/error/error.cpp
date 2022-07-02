/*
** EPITECH PROJECT, 2022
** error
** File description:
** error
*/

#include "error.hpp"

Errors::Errors(std::ostream &os, const std::string &message) throw()
    : Os(os)
{
    errorMessage = message;
}

Errors::~Errors(void) throw()
{
}

const char *Errors::what(void) const throw()
{
    return errorMessage.c_str();
}
