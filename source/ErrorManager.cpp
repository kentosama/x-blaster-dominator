/* 
 * File:   ErrorManager.cpp
 * Author: jacques belosoukinski
 * 
 * Created on 27 avril 2013, 07:40
 */

#include "ErrorManager.h"

ErrorManager* ErrorManager::m_pInstance = NULL;

ErrorManager* ErrorManager::Instance() {
    if (!m_pInstance)
        m_pInstance = new ErrorManager;
    return m_pInstance;
}

ErrorManager::ErrorManager() {

#ifdef __linux 
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    path = string(homedir) + "/.x-blaster dominator/error-log.txt";
#elif _WIN32 || _WIN64
    char path[ MAX_PATH ];
    SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path);
    string pathFile = strcat(path, "\\My Games\\X-Blaster Dominator\\");
    boost::filesystem::path dir(pathFile);
    if (!boost::filesystem::exists(dir))
        boost::filesystem::create_directories(dir);
    this->path = pathFile + "error-log.txt";

#endif

    setLanguage();
}

ErrorManager::ErrorManager(const ErrorManager& orig) {
}

ErrorManager::~ErrorManager() {
}

void ErrorManager::save(const unsigned char error, string information) {
    if (information != "")
        information = "- " + information + "\n";
    if (error < 5) {
#ifdef _DEBUG
        std::cout << this->error[error] << std::endl;
        std::cout << information << std::endl;
#endif
        ofstream log_file;
        log_file.open(path, std::ios::out | std::ios::app);
        time_t time_now = std::time(0);
        char* dt = ctime(&time_now);
        log_file << dt << this->error[error] + " " << this->error[5] << information << std::endl;
        log_file.close();
    }
    close();
}

void ErrorManager::close() {
    if (WindowGame::Instance()->window.isOpen())
        WindowGame::Instance()->window.close();
    exit(EXIT_FAILURE);
}

void ErrorManager::setLanguage() {
    if (Language::Instance()->language == "french")
        error = Language::Instance()->french[6];
    else if (Language::Instance()->language == "english")
        error = Language::Instance()->english[6];
}