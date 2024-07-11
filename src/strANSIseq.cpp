#include <strANSIseq.hpp>

namespace ESC
{

int CLI::s_verbose_max = -1;

std::string fstr(std::string v, std::initializer_list<int> l)
{
    std::string seq_str = "\x1b[";
    for(auto i : l) seq_str += ";" + std::to_string(i);
    return seq_str + "m" + v + "\x1b[0m";
}

std::string fstr_link(std::string link, std::string text)
{
    return "\e]8;;" + link + "\e\\" + ((text == "") ? link : text) +
           "\e]8;;\e\\";
}

std::string move_type(int n, char type)
{
    return "\x1b[" + std::to_string(n) + type;
}

std::string move_up(int n) { return move_type(n, 'A'); }
std::string move_down(int n) { return move_type(n, 'B'); }
std::string move_right(int n) { return move_type(n, 'C'); }
std::string move_left(int n) { return move_type(n, 'D'); }

std::string move_to(int line, int column)
{
    return "\x1b[" + std::to_string(line) + ";" + std::to_string(column) + "f";
}

int get_pos(int *y, int *x)
{
    char buf[30] = {0};
    int ret, i, pow;
    char ch;

    *y = 0;
    *x = 0;

#ifdef __linux__
    struct termios term, restore;

    tcgetattr(0, &term);
    tcgetattr(0, &restore);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);

    write(1, "\033[6n", 4);
#elif _WIN32 //to be tested
    DWORD dwRead;
    char c;
    DWORD dwMode;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(hStdin, &dwMode);
    SetConsoleMode(hStdin,
                   dwMode & (~ENABLE_ECHO_INPUT) & (~ENABLE_LINE_INPUT));

    WriteFile(hStdin, "\033[6n", 4, &dwRead, NULL);
#endif

#ifdef __linux__
    for(i = 0, ch = 0; ch != 'R'; i++)
    {
        ret = read(0, &ch, 1);
        buf[i] = ch;
    }
#elif _WIN32 //to be tested
    for(i = 0, ch = 0; ch != 'R'; i++)
    {
        ReadFile(hStdin, &c, 1, &dwRead, NULL);
        buf[i] = c;
        ch = c;
    }
#endif

    for(i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
        *x = *x + (buf[i] - '0') * pow;

    for(i--, pow = 1; buf[i] != '['; i--, pow *= 10)
        *y = *y + (buf[i] - '0') * pow;

#ifdef __linux__
    tcsetattr(0, TCSANOW, &restore);
#elif _WIN32 //to be tested
    SetConsoleMode(hStdin, dwMode);
#endif

    return 0;
}

}; // namespace ESC
