#include <iostream>
#include <strANSIseq.hpp>

int
main(int argc, char **argv)
{

  std::cout << "hello " << ESC::format("hey", {ESC::STRIKE, ESC::FG_CYAN})
         << " hello" << std::endl
         << std::endl;

    std::string str;
    std::cout << ESC::move_to(5, 10);
    std::cout << std::endl << "voila: " << str << std::endl;
    return 0;
}
