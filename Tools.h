//
// Created by firgaty on 20/02/17.
//

#ifndef UNI_TOOLS_H
#define UNI_TOOLS_H

#include <iostream>
#include <deque>

class Tools {

public:
    static std::string intToString(int i);
    static void writeInFile(std::string str, bool eraseFile);

    static void addDeque(std::deque<int> *a, std::deque<int> *b);
};


#endif //UNI_TOOLS_H
