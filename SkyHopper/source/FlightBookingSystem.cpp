#include "FlightBookingSystem.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <filesystem>
FlightBookingSystem::FlightBookingSystem(const std::string& citiesFile) {
    std::srand(std::time(0));
    loadCities(citiesFile);
}

void FlightBookingSystem::loadCities(const std::string& citiesFile) {
    std::ifstream file(citiesFile);
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find_last_of('(');
        std::string name = line.substr(0, pos - 1);
        std::string code = line.substr(pos + 1, 3);
        cities.emplace_back(name, code);
    }
}

void FlightBookingSystem::showMainMenu() {
    int choice;
    std::string username, password;

    do {
        if (loggedInUser.empty()) {
            std::cout << "1. Login\n2. Create Account\n3. Exit\n";
        } else {
            std::cout << "1. Search Flights\n2. Show Booked Flights\n3. Logout\n";
        }

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (loggedInUser.empty()) {
                    std::cout << "Enter username: ";
                    std::cin >> username;
                    std::cout << "Enter password: ";
                    std::cin >> password;

                    if (checkCredentials(username, password)) {
                        std::cout << "Login successful!" << std::endl;
                    } else {
                        std::cout << "Invalid username or password." << std::endl;
                    }
                } else {
                    searchFlights();
                }
            break;
            case 2:
                if (loggedInUser.empty()) {
                    std::cout << "Enter new username: ";
                    std::cin >> username;
                    std::cout << "Enter new password: ";
                    std::cin >> password;
                    saveCredentials(username, password);
                    std::cout << "Account created successfully!" << std::endl;
                } else {
                    showBookedFlights();
                }
            break;
            case 3:
                if (!loggedInUser.empty()) {
                    std::cout << "Logging out..." << std::endl;
                    loggedInUser.clear(); // Clear the logged-in user
                }
            break;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }
    } while (choice != 3);
}


void FlightBookingSystem::searchFlights() {
    int departureIndex, arrivalIndex;
    std::string date;
    int timeOption;

    std::cout << "Select departure city:\n";
    for (size_t i = 0; i < cities.size(); ++i) {
        std::cout << i + 1 << ". " << cities[i].getName() << "\n";
    }
    std::cin >> departureIndex;

    std::cout << "Select arrival city:\n";
    for (size_t i = 0; i < cities.size(); ++i) {
        if (i + 1 != departureIndex)
            std::cout << i + 1 << ". " << cities[i].getName() << "\n";
    }
    std::cin >> arrivalIndex;

    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> date;

    std::cout << "Select departure time option:\n";
    std::cout << "1. Morning (08:00 - 11:59)\n";
    std::cout << "2. Afternoon (12:00 - 15:59)\n";
    std::cout << "3. Evening (16:00 - 19:59)\n";
    std::cout << "4. Night (20:00 - 23:59)\n";
    std::cin >> timeOption;

    std::string time;
    switch (timeOption) {
        case 1:
            time = "08:00";
        break;
        case 2:
            time = "12:00";
        break;
        case 3:
            time = "16:00";
        break;
        case 4:
            time = "20:00";
        break;
        default:
            std::cout << "Invalid choice, defaulting to morning time.\n";
        time = "08:00";
    }

    std::string departure = cities[departureIndex - 1].getName();
    std::string arrival = cities[arrivalIndex - 1].getName();

    bookFlight(departure, arrival, date, time);
}



void FlightBookingSystem::bookFlight(const std::string& departure, const std::string& arrival, const std::string& date, const std::string& time) {
    std::string name, surname, personalID;

    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Enter your surname: ";
    std::cin >> surname;
    std::cout << "Enter your personal ID: ";
    std::cin >> personalID;

    Booking booking(name, surname, personalID, departure, arrival, date, time, generateGateNumber(), generateFlightNumber(), generateSeatNumber());
    bookings.push_back(booking);

    // Pass loggedInUser as the username parameter
    saveBooking(booking.getName() + " " + booking.getSurname() + " " + booking.getFlightNumber() + " " + booking.getDeparture() + " (" + booking.getDate() + " " + booking.getTime() + ") " + booking.getArrival() + " Gate: " + booking.getGateNumber() + " Seat: " + booking.getSeatNumber());
}


void FlightBookingSystem::printBoardingPass(const Booking& booking) {
    std::cout << "\n--- Boarding Pass ---\n";
    std::cout << "Name: " << booking.getName() << " " << booking.getSurname() << "\n";
    std::cout << "Flight: " << booking.getFlightNumber() << "\n";

    std::cout << "From: " << booking.getDeparture() << " (" << booking.getDate() << " " << booking.getTime() << ")\n";
    std::cout << "To: " << booking.getArrival() << "\n";
    std::cout << "Gate: " << booking.getGateNumber() << "\n";
    std::cout << "Seat: " << booking.getSeatNumber() << "\n";
    std::cout << "GATE CLOSES 15 MIN BEFORE DEPARTURE\n";
    std::cout << "----------------------\n";
}

std::string FlightBookingSystem::generateGateNumber() const {
    return std::to_string(1 + rand() % 3) + static_cast<char>('A' + rand() % 11);
}

std::string FlightBookingSystem::generateFlightNumber() const {
    return std::string(1, 'A' + rand() % 26) + std::string(1, 'A' + rand() % 26) + std::to_string(1000 + rand() % 9000);
}

std::string FlightBookingSystem::generateSeatNumber() const {
    return std::to_string(1 + rand() % 31) + static_cast<char>('A' + rand() % 6);
}

void FlightBookingSystem::saveCredentials(const std::string &username, const std::string &password) {
    std::ofstream file("database.txt", std::ios_base::app);
    if (!file) {
        // File does not exist, create it
        file.open("database.txt", std::ios_base::out);
        if (!file) {
            std::cerr << "Error: Unable to create database file." << std::endl;
            return;
        }
    }

    file << username << ":" << password << std::endl;
    std::cout << "Credentials saved successfully." << std::endl;
    file.close();
}

void FlightBookingSystem::saveBooking(const std::string& bookingDetails) {
    std::string bookingsFilePath = "bookings/" + loggedInUser + ".txt";

    std::ofstream file(bookingsFilePath, std::ios_base::app);
    if (!file) {
        std::cerr << "Error: Unable to open bookings file." << std::endl;
        return;
    }

    file << bookingDetails << std::endl;
    std::cout << "Booking saved successfully." << std::endl;
    file.close();
}






bool FlightBookingSystem::checkCredentials(const std::string &username, const std::string &password) {
    std::ifstream file("database.txt");
    if (!file) {
        std::cerr << "Error: Unable to open database file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string storedUsername, storedPassword;
        if (std::getline(iss, storedUsername, ':') && std::getline(iss, storedPassword)) {
            if (storedUsername == username && storedPassword == password) {
                file.close();
                loggedInUser = username; // Set the currently logged in user
                return true;
            }
        }
    }

    file.close();
    return false;
}


void FlightBookingSystem::showBookedFlights() {
    std::string bookingsFilePath = "bookings/" + loggedInUser + ".txt";
    std::ifstream file(bookingsFilePath);
    if (!file) {
        std::cerr << "Error: Unable to open bookings file for user " << loggedInUser << "." << std::endl;
        return;
    }

    std::cout << "Booked flights for " << loggedInUser << ":\n";
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, surname, flightNumber, departure, arrival, gate, seat;
        std::string date, time;

        // Read name and surname
        iss >> name >> surname;

        // Read flight number
        iss >> flightNumber;

        // Read departure city and airport
        std::string departureCity, departureAirport;
        iss >> departureCity >> departureAirport;
        departure = departureCity + " " + departureAirport;

        // Read date and time
        iss >> date >> time;

        // Read arrival city and airport
        std::string arrivalCity, arrivalAirport;
        iss >> arrivalCity >> arrivalAirport;
        arrival = arrivalCity + " " + arrivalAirport;

        // Read gate and seat
        iss >> gate >> seat;

        std::cout << "Name: " << name << " " << surname << "\n";
        std::cout << "Flight: " << flightNumber << "\n";
        std::cout << "From: " << departure << " (" << date << " " << time << ")\n";
        std::cout << "To: " << arrival << "\n";
        std::cout << "Gate: " << gate << "\n";
        std::cout << "Seat: " << seat << "\n";
        std::cout << "GATE CLOSES 15 MIN BEFORE DEPARTURE\n";
        std::cout << "----------------------\n";
    }

    file.close();
}















