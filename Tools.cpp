//
// Created by firgaty on 20/02/17.
//

#include "Tools.h"
#include <sstream>
#include <fstream>

std::string Tools::intToString(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

void Tools::writeInFile(std::string s, bool eraseFile) {
    std::ofstream file;

    if(eraseFile) {
        file.open("results.txt", std::ios::out | std::ios::trunc);
    } else {
        file.open("results.txt", std::ios::out | std::ios::app);
    }

    if(file) {
        file << s << std::endl;

    } else {
        std::cout << "ERROR: File not reachable." << std::endl;
    }

}
