/* 
 * File:   ErrorManager.h
 * Author: jacques belosoukinski
 *
 * Created on 27 avril 2013, 07:40
 */

#ifndef ERRORMANAGER_H
#define	ERRORMANAGER_H
#include <SFML/Graphics.hpp>
#include <ostream>
#include <string>
#include <vector>
#include "Language.h"
#include "WindowGame.h"

using std::string;
using std::vector;
using std::ofstream;


class ErrorManager {
public:
    static ErrorManager* Instance();
    ErrorManager();
    ErrorManager(const ErrorManager& orig);
    void save(const unsigned char error, string information);
    void close();
    void setLanguage();
    virtual ~ErrorManager();
private:
    static ErrorManager* m_pInstance;
    
    string path;
    vector<string> error;

};

#endif	/* ERRORMANAGER_H */

