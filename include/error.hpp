/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** include
*/

#pragma once
#include <exception>
#include <iostream>
#include <string>

class Errors : public std::exception {
public:
    /**
     * @brief Construct a new Errors object
     *
     */
    Errors(std::ostream &, const std::string &) throw();

    /**
     * @brief Destroy the Errors object
     *
     */
    virtual ~Errors(void) throw();

    /**
     * @brief Return `errorMessage` in char *
     *
     * @return const char*
     */
    const char *what(void) const throw();

private:
    std::string errorMessage;
    std::ostream &Os;
};
