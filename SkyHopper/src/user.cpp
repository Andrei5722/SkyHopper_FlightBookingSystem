
#include "../include/user.h"
#include <iostream>
#include <fstream>
#include <algorithm>

User::User() {}

User::User(std::string username, std::string password) : username(username), password(password) {}

bool User::signup() {
    std::ifstream infile("../data/users.txt");
    std::string user, pass;
    while (infile >> user >> pass) {
        if (user == username) {
            std::cout << "Username already exists. Please choose another username." << std::endl;
            return false;
        }
    }
    infile.close();

    std::ofstream outfile("../data/users.txt", std::ios::app);
    outfile << username << " " << password << std::endl;
    outfile.close();

    std::cout << "Signup successful!" << std::endl;
    return true;
}

bool User::login() {
    std::ifstream infile("../data/users.txt");
    std::string user, pass;
    while (infile >> user >> pass) {
        if (user == username && pass == password) {
            std::cout << "Login successful!" << std::endl;
            infile.close();
            return true;
        }
    }
    infile.close();
    std::cout << "Invalid username or password." << std::endl;
    return false;
}

void User::logout() {
    std::cout << "Logged out successfully!" << std::endl;
}

std::string User::getUsername() const {
    return username;
}
