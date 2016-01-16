/* 
 * File:   MessageManager.cpp
 * Author: Jacques
 * 
 * Created on 29 septembre 2013, 13:17
 */

#include "MessageManager.h"

MessageManager* MessageManager::m_Instance = NULL;

MessageManager* MessageManager::Instance() {
    if (!m_Instance)
        m_Instance = new MessageManager;
    return m_Instance;
}

MessageManager::MessageManager() {
}

MessageManager::MessageManager(const MessageManager& orig) {
}

MessageManager::~MessageManager() {
    messages.reserve(4);
    setLanguage();
    windowsbox.reserve(1);
}

void MessageManager::setLanguage() {
    if (Language::Instance()->language == "english")
        messages = Language::Instance()->english[2];
    else messages = Language::Instance()->french[2];
}

void MessageManager::addMessage(unsigned char message, int position) {
    if(windowsbox.size() >= 1) {
        windowsbox.erase(windowsbox.end());
    }
    
    if(windowsbox.size() < 1)
    windowsbox.emplace_back(messages[message]);
}

void MessageManager::update() {
    if(windowsbox.size() == 1) {
            if (!windowsbox.back().active)
                windowsbox.erase(windowsbox.end());
            else windowsbox.back().update();
    }
}