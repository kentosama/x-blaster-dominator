/* 
 * File:   Functions.cpp
 * Author: Jacques
 * 
 * Created on 8 février 2014, 12:04
 */

#include "Functions.h"

Functions* Functions::mp_Instance = NULL;

Functions* Functions::Instance() {
    if(!mp_Instance)
        mp_Instance = new Functions;
    return mp_Instance;
}
Functions::Functions() {
}

Functions::Functions(const Functions& orig) {
}

Functions::~Functions() {
}

std::string Functions::toString(bool value){
    std::stringstream ss;
    std::string string;
    ss << value;
    ss >> string;
    return string;
}

