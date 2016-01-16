/* 
 * File:   Language.h
 * Author: jacques belosoukinski
 *
 * Created on 26 mars 2013, 09:13
 */

#ifndef LANGUAGE_H
#define	LANGUAGE_H

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <ostream>
#ifdef __linux
#include <sys/types.h>
#include <pwd.h>
#elif _WIN32 || _WIN64
#include <shlobj.h>
#include <windows.h>
#include <io.h>
#endif
using std::vector;
using std::string;
using std::wstring;
using std::stringstream;
using std::ifstream;
using std::ofstream;


class Language {
public:
    static Language* Instance();
    void load();
    void save();
    string language;
    vector<vector<string>> english;
    vector<vector<string>> french;
    vector<string> names;
    

private:
    Language();
    Language(const Language& orig);
    virtual ~Language();
    static Language* m_pInstance;
    void generate();
    void create();
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & english;
        ar & french;
        ar & language;
    }
    
    string languageFile;  
};

#endif	/* LANGUAGE_H */

