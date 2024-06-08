
#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;

public:
    User();
    User(std::string username, std::string password);

    bool signup();
    bool login();
    void logout();
    std::string getUsername() const;
};

#endif // USER_H
