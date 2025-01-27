#include <strANSIseq.hpp>

namespace ESC
{

int CLI::s_verbose_max = -1;

std::string fstr(std::string v, std::initializer_list<int> l)
{
#if defined(__linux__) || defined(__APPLE__)
    std::string seq_str = "\x1B[";
    for(auto i : l) seq_str += ";" + std::to_string(i);
    return seq_str + "m" + v + "\x1B[0m";
#elif _WIN32
    std::string seq_str = "`e[";
    for(auto i : l) seq_str += ";" + std::to_string(i);
    return seq_str + "m" + v + "`e[0m oo";
#endif
}

std::string fstr_link(std::string link, std::string text)
{
    return "\x1B]8;;" + link + "\x1B\\" + ((text == "") ? link : text) +
           "\x1B]8;;\x1B\\";
}

std::string move_type(int n, char type)
{
    return "\x1B[" + std::to_string(n) + type;
}

std::string move_up(int n) { return move_type(n, 'A'); }
std::string move_down(int n) { return move_type(n, 'B'); }
std::string move_right(int n) { return move_type(n, 'C'); }
std::string move_left(int n) { return move_type(n, 'D'); }

std::string move_to(int line, int column)
{
    return "\x1B[" + std::to_string(line) + ";" + std::to_string(column) + "f";
}

int get_pos(int *y, int *x)
{
    char buf[30] = {0};
    int i, pow;
    char ch;

    *y = 0;
    *x = 0;

#if defined(__linux__) || defined(__APPLE__)
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

#if defined(__linux__) || defined(__APPLE__)
    int ret = 0;
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

#if defined(__linux__) || defined(__APPLE__)
    tcsetattr(0, TCSANOW, &restore);
#elif _WIN32 //to be tested
    SetConsoleMode(hStdin, dwMode);
#endif

    if(ret < 0)
        return -1;
    return 0;
}

}; // namespace ESC
