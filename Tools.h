//
// Created by firgaty on 20/02/17.
//

#ifndef UNI_TOOLS_H
#define UNI_TOOLS_H

#include <iostream>

class Tools {

public:
    static std::string intToString(int i);
    static void writeInFile(std::string str, bool eraseFile);
};


#endif //UNI_TOOLS_H
