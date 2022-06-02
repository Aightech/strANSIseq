#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>

namespace ESC
{
enum FORMAT
{
    BOLD = 1,
    DIM = 2,
    ITALIC = 3,
    UNDERLINE = 4,
    BLINK_SLOW = 5,
    BLINK_FAST = 6,
    REVERSE = 7,
    HIDDEN = 8,
    STRIKE = 9,

    FG_BLACK = 30,
    BG_BLACK = 40,
    FG_RED = 31,
    BG_RED = 41,
    FG_GREEN = 32,
    BG_GREEN = 42,
    FG_YELLOW = 33,
    BG_YELLOW = 43,
    FG_BLUE = 34,
    BG_BLUE = 44,
    FG_MAGENTA = 35,
    BG_MAGENTA = 45,
    FG_CYAN = 36,
    BG_CYAN = 46,
    FG_WHITE = 37,
    BG_WHITE = 47,
    FG_DEFAULT = 39,
    BG_DEFAULT = 49
};

std::string
format(std::string v, std::initializer_list<int> l);

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
