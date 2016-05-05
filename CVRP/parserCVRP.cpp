#include "CVRP.hpp"

int main(int argc, char** argv){

  if (argc > 1) {
    CVRPData cvrp(argv[1]);
    std::cout << cvrp << std::endl;
  }


  return 0;
}
