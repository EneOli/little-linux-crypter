#include <iostream>
#include <fstream>
#include <sstream>


int main(int argc, char* argv[]) {
    
    if(argc < 2) {
        std::cerr << "Please specify payload" << std::endl;
        return -1;
    }

    std::ifstream input(argv[1]);
    std::stringstream sinput;
    
    if(input.is_open()) {
        sinput << input.rdbuf();
    } else {
        std::cerr << "could not open payload" << std::endl;
        return -1;
    }

    std::ifstream stub("stub");
    std::stringstream sstub;
    
    if(stub.is_open()) {
        sstub << stub.rdbuf();
    } else {
        std::cerr << "could not open stub" << std::endl;
        return -1;
    }

    std::ofstream final("final");

    if(!final.is_open()) {
        std::cerr << "could not open final" << std::endl;
        return -1;
    }

     final << sstub.str() << "[crypt]" << sinput.str() << "[crypt]";

    std::cout << "done" << std::endl;

    return 0;
}