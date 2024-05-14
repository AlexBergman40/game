#include <iostream>
#include <bitset>
#include <cstdint>

int main(int argc, char *argv[])
{
  int64_t square = 0b1111111100000000000000000000000000000000000000000000000000000000;

  std::cout << std::bitset<64>(square) << std::endl;

  int64_t mask = square << 8;

  std::cout << std::bitset<64>(mask) << std::endl;

  mask == 0 ? std::cout << "true" : std::cout << "false";
}