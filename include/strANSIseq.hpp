#ifndef STR_ANSI_SEQ_HPP
#define STR_ANSI_SEQ_HPP

#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <termios.h>

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
    BOLD = 1,       //!< Bold text.
    DIM = 2,        //!< Dim text.
    ITALIC = 3,     //!< Italic text.
    UNDERLINE = 4,  //!< Underlined text.
    BLINK_SLOW = 5, //!< Slow blinking text.
    BLINK_FAST = 6, //!< Fast blinking text.
    REVERSE = 7,    //!< Reversed text.
    HIDDEN = 8,     //!< Hidden text.
    STRIKE = 9,     //!< Striked text.

    FG_BLACK = 30,   //!< Black foreground.
    BG_BLACK = 40,   //!< Black background.
    FG_RED = 31,     //!< Red foreground.
    BG_RED = 41,     //!< Red background.
    FG_GREEN = 32,   //!< Green foreground.
    BG_GREEN = 42,   //!< Green background.
    FG_YELLOW = 33,  //!< Yellow foreground.
    BG_YELLOW = 43,  //!< Yellow background.
    FG_BLUE = 34,    //!< Blue foreground.
    BG_BLUE = 44,    //!< Blue background.
    FG_MAGENTA = 35, //!< Magenta foreground.
    BG_MAGENTA = 45, //!< Magenta background.
    FG_CYAN = 36,    //!< Cyan foreground.
    BG_CYAN = 46,    //!< Cyan background.
    FG_WHITE = 37,   //!< White foreground.
    BG_WHITE = 47,   //!< White background.
    FG_DEFAULT = 39, //!< Default foreground.
    BG_DEFAULT = 49  //!< Default background.
};

/**
 * @brief fstr Prints a formated string.
 *
 * @param v String to format.
 * @param l List of ANSI format parameters.
 * @return std::string Returns the formated string.
 */
std::string fstr(std::string v, std::initializer_list<int> l);

template <typename T>
std::string fstr_n(T v, std::initializer_list<int> l)
{
    return fstr(std::to_string(v), l);
};

std::string fstr_link(std::string link, std::string text = "");

std::string move_type(int n, char type);

std::string move_up(int n = 1);

std::string move_down(int n = 1);

std::string move_right(int n = 1);

std::string move_left(int n = 1);

std::string move_to(int line, int column);

int get_pos(int *y, int *x);

class CLI
{
    public:
    CLI(int verbose, std::string id)
    {
        if(verbose > s_verbose_max)
            s_verbose_max = verbose;
        m_verbose = verbose;
        if(verbose >= 0 && verbose < 9)
            m_id = fstr(id, {FG_YELLOW + verbose});
    };

    std::string &cli_id() { return m_id; };

    void log(std::string msg, bool id = false)
    {
        if(m_verbose)
        {
            printf("%s", msg.c_str());
            fflush(stdout);
        }
    };

    void logln(std::string msg, bool id = false)
    {
        if(m_verbose)
        {
            if(id)
	      {
                printf("[%s]", m_id.c_str());
		fflush(stdout);
		int x;
		get_pos(&x, &m_indent);
		printf(" %s\n", msg.c_str());
	      }
            else
                printf("%*s%s\n", m_indent, "", msg.c_str());

        }
    };

    std::string log_error(std::string msg)
    {
        return "[" + m_id + "] " + fstr("ERROR: ", {BOLD, FG_RED}) + msg;
    };

    static int s_verbose_max;

    private:
    int m_verbose;
    std::string m_id;
    int m_indent=10;
};
}; // namespace ESC

#endif //STR_ANSI_SEQ_HPP
