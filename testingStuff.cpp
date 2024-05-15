#include <iostream>
//limit west/east movement, north/south movement
#include <bitset>
#include <cstdint>

int main(int argc, char *argv[])
{
  uint64_t square = 0b1111111110000000000000000000000000000000000000000000000000000000;

  std::cout << std::bitset<64>(square) << std::endl;

  uint64_t mask = square << 8;

  std::cout << std::bitset<64>(mask) << std::endl;

  mask == 0 ? std::cout << "true" : std::cout << "false";
}