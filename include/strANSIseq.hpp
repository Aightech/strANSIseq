#ifndef STR_ANSI_SEQ_HPP
#define STR_ANSI_SEQ_HPP

#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>

#define LOG(...)             \
    if(m_verbose)            \
    {                        \
        printf(__VA_ARGS__); \
        fflush(stdout);      \
    }

/**
 * @brief This namespace contains all the functions to print formated (colored, striked, blinking) text.
 *
 */
namespace ESC
{
/*! This enum contains all the ANSI escape sequences. */
enum FORMAT
{
    BOLD = 1, //!< Bold text. 
    DIM = 2, //!< Dim text.
    ITALIC = 3, //!< Italic text.
    UNDERLINE = 4, //!< Underlined text.
    BLINK_SLOW = 5, //!< Slow blinking text.
    BLINK_FAST = 6, //!< Fast blinking text.
    REVERSE = 7, //!< Reversed text.
    HIDDEN = 8, //!< Hidden text.
    STRIKE = 9, //!< Striked text.

    FG_BLACK = 30, //!< Black foreground.
    BG_BLACK = 40, //!< Black background. 
    FG_RED = 31, //!< Red foreground.
    BG_RED = 41, //!< Red background.
    FG_GREEN = 32, //!< Green foreground.
    BG_GREEN = 42, //!< Green background.
    FG_YELLOW = 33, //!< Yellow foreground.
    BG_YELLOW = 43, //!< Yellow background.
    FG_BLUE = 34, //!< Blue foreground.
    BG_BLUE = 44, //!< Blue background.
    FG_MAGENTA = 35, //!< Magenta foreground.
    BG_MAGENTA = 45, //!< Magenta background.
    FG_CYAN = 36, //!< Cyan foreground.
    BG_CYAN = 46, //!< Cyan background.
    FG_WHITE = 37, //!< White foreground.
    BG_WHITE = 47, //!< White background.
    FG_DEFAULT = 39, //!< Default foreground.
    BG_DEFAULT = 49 //!< Default background.
};

/**
 * @brief fstr Prints a formated string.
 * 
 * @param v String to format.
 * @param l List of ANSI format parameters.
 * @return std::string Returns the formated string.
 */
std::string
fstr(std::string v, std::initializer_list<int> l);

std::string
move_type(int n, char type);

std::string
move_up(int n = 1);

std::string
move_down(int n = 1);

std::string
move_right(int n = 1);

std::string
move_left(int n = 1);

std::string
move_to(int line, int column);
}; // namespace ESC

#endif //STR_ANSI_SEQ_HPP