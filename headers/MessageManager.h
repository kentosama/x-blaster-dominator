/* 
 * File:   MessageManager.h
 * Author: Jacques
 *
 * Created on 29 septembre 2013, 13:17
 */

#ifndef MESSAGEMANAGER_H
#define	MESSAGEMANAGER_H

#include <cstddef>
#include <vector>
#include <string>
#include "WindowBox.h"
#include "Language.h"

class MessageManager {
public:
    static MessageManager * Instance();
    MessageManager();
    MessageManager(const MessageManager& orig);
    virtual ~MessageManager();
    void setLanguage();
    void update();
    void addMessage(unsigned char message, int position);
    std::vector<WindowBox> windowsbox;
private:
    static MessageManager * m_Instance;
    std::vector<string> messages;
};

#endif	/* MESSAGEMANAGER_H */

