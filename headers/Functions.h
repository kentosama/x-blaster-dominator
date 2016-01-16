/* 
 * File:   Functions.h
 * Author: Jacques
 *
 * Created on 8 février 2014, 12:04
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H
#include <unistd.h>
#include <string>
#include <sstream>

class Functions {
public:
    static Functions* Instance();
    Functions();
    Functions(const Functions& orig);
    virtual ~Functions();
    std::string toString(bool value);
private:
    static Functions* mp_Instance;

};

#endif	/* FUNCTIONS_H */

