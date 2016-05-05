#include "CARP.hpp"

int main(int argc, char** argv){

  if (argc > 1) {
    CARPData carp(argv[1]);
    std::cout << carp << std::endl;
  }


  return 0;
}
