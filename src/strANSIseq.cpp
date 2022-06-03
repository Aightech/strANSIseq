#include <strANSIseq.hpp>


namespace ESC
{

std::string
fstr(std::string v, std::initializer_list<int> l)
{
    std::string seq_str = "\x1b[";
    for(auto i : l) seq_str += ";" + std::to_string(i);
    return seq_str + "m" + v + "\x1b[0m";
}


std::string
move_type(int n, char type)
{
    return "\x1b[" + std::to_string(n) + type;
}

std::string
move_up(int n)
{
    return move_type(n, 'A');
}
std::string
move_down(int n)
{
    return move_type(n, 'B');
}
std::string
move_right(int n)
{
    return move_type(n, 'C');
}
std::string
move_left(int n)
{
    return move_type(n, 'D');
}

std::string
move_to(int line, int column)
{
    return "\x1b[" + std::to_string(line) + ";" + std::to_string(column) + "f";
}

}; // namespace ESC
