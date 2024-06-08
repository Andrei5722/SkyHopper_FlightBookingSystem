#include "../include/flightmanagementsystem.h"
#include "../include/flight.h"
#include "../include/tools.h"
#include "../include/user.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <vector>
#include <string>
#include <algorithm>

std::string toLowerCase(std::string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

std::string generateFlightNumber() {
    // Generate random characters for the first 2 characters of the flight number
    std::string flightNumber;
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, alphabet.size() - 1);
    for (int i = 0; i < 2; ++i) {
        flightNumber += alphabet[dis(gen)];
    }

    // Generate random digits for the last 4 characters of the flight number
    std::uniform_int_distribution<> digitDis(0, 9);
    for (int i = 0; i < 4; ++i) {
        flightNumber += std::to_string(digitDis(gen));
    }

    return flightNumber;
}

void FlightManagementSystem::loadFlights() {
        flights.clear();
        std::ifstream infile("../data/flights.txt");
        int id, seats;
        std::string destination, departureTimes;
        while (infile >> id >> destination >> departureTimes >> seats) {
            flights.push_back(Flight(id, destination, departureTimes, seats));
        }
        infile.close();
    }

void FlightManagementSystem::generateBoardingPass(const Flight& flight, const std::string& departureCity, const std::string& date, const std::string& time, const std::string& name, int age, const std::string& gender) {
    std::string filename = currentUser.getUsername() + "_ticket.txt";
    std::ofstream outfile(filename);
    int randomSeatNumber = rand() % flight.availableSeats + 1; // Random seat number within available seats range
    char randomSeatChar = 'A' + rand() % 6; // Random character from A to F
    std::string seatNumber = std::to_string(randomSeatNumber) + randomSeatChar;

    outfile << "*****************************\n";
    outfile << "*       BOARDING PASS       *\n";
    outfile << "*****************************\n";
    outfile << "Flight Number: " << generateFlightNumber() << std::endl; // Generate and include flight number
    outfile << "From: " << departureCity << std::endl;
    outfile << "To: " << flight.destination << std::endl;
    outfile << "Departure Time: " << time << std::endl;
    outfile << "Seat: " << seatNumber << std::endl;
    outfile << "Passenger Name: " << name << std::endl;
    outfile << "Age: " << age << std::endl;
    outfile << "Gender: " << gender << std::endl;
    outfile << "*****************************************\n";
    outfile << "*  GATE CLOSES 15 MIN BEFORE DEPARTURE  *\n"; // Updated message
    outfile << "*****************************************\n";
    outfile.close();

    // Print the boarding pass to the console
    std::ifstream infile(filename);
    std::string line;
    std::cout << '\n';
    std::cout << '\n';
    while (getline(infile, line)) {
        std::cout << "\t\t" << line << std::endl; // Add tabs only to center the boarding pass message
    }
    std::cout << '\n';
    std::cout << '\n';
    std::cout << "Press enter to continue...";
    std::cin.ignore();
    std::cin.get();
    infile.close();
}

void FlightManagementSystem::addFlight() {
    if (!isAdmin) {
        std::cout << "Admin access required to add flights." << std::endl;
        return;
    }

    int id, seats;
    std::string destination, departureTimes;
    std::cout << "Enter flight ID: ";
    std::cin >> id;
    std::cout << "Enter destination: ";
    std::cin >> destination;
    std::cout << "Enter departure times (comma separated, e.g., 12:00,16:00,18:00): ";
    std::cin.ignore();
    std::getline(std::cin, departureTimes);
    std::cout << "Enter available seats: ";
    std::cin >> seats;

    Flight flight(id, destination, departureTimes, seats);
    flight.saveToFile();
    flights.push_back(flight);

    std::cout << "Flight added successfully!" << std::endl;
}

void FlightManagementSystem::addDepartureCity() {
    if (!isAdmin) {
        std::cout << "Admin access required to add departure cities." << std::endl;
        return;
    }

    std::string city;
    std::cout << "Enter departure city: ";
    std::cin >> city;

    std::ofstream outfile("../data/departure_cities.txt", std::ios::app);
    outfile << city << std::endl;
    outfile.close();

    std::cout << "Departure city added successfully!" << std::endl;
}

void FlightManagementSystem::viewBookings() {
    std::string filename = currentUser.getUsername() + "_bookings.txt";
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "No bookings found for this user." << std::endl;
        return;
    }

    int bookingNumber = 1;
    std::cout << "Your Bookings:" << std::endl;
    std::cout << "--------------" << std::endl;
    int flightId;
    std::string destination, departureCity, date, time, name, gender;
    int age;
    while (infile >> flightId >> destination >> departureCity >> date >> time >> name >> age >> gender) {
        std::cout << bookingNumber << ". ";
        std::cout << "Flight ID: " << flightId << ", Destination: " << destination
            << ", Departure City: " << departureCity << ", Date: " << date
            << ", Time: " << time 
            << ", Passenger Name: " << name << ", Age: " << age
            << ", Gender: " << gender << std::endl;
        bookingNumber++;
    }
    infile.close();

    // Prompt the user to select a booking
    std::cout << "Enter the booking number to view boarding pass (0 to go back): ";
    int choice;
    std::cin >> choice;
    if (choice == 0) return;

    int currentBooking = 1;
    infile.open(filename);
    while (infile >> flightId >> destination >> departureCity >> date >> time >>  name >> age >> gender) {
        if (currentBooking == choice) {
            Flight flight(flightId, destination, time, 50);
            generateBoardingPass(flight, departureCity, date, time, name, age, gender);
            break;
        }
        currentBooking++;
    }
    infile.close();
}



void FlightManagementSystem::viewFlights() {
    loadFlights();
    if (flights.empty()) {
        std::cout << "No flights available." << std::endl;
        return;
    }

    for (const auto& flight : flights) {
        std::cout << "ID: " << flight.id << ", Destination: " << flight.destination
                  << ", Departure Times: " << flight.departureTimes
                  << ", Available Seats: " << flight.availableSeats << std::endl;
    }
    std::cin.ignore();
}

bool FlightManagementSystem::isValidDepartureCity(const std::string& city) {
    std::ifstream infile("departure_cities.txt");
    std::string availableCity;
    while (infile >> availableCity) {
        if (toLowerCase(availableCity) == toLowerCase(city)) {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}

void FlightManagementSystem::saveBookingDetails(const Flight& flight, const std::string& departureCity, const std::string& date, const std::string& time, const std::string& name, int age, const std::string& gender) {
    std::string filename = currentUser.getUsername() + "_bookings.txt";
    std::ofstream outfile(filename, std::ios::app);
    outfile << flight.id << " " << flight.destination << " " << departureCity << " " << date << " " << time << " " << name << " " << age << " " << gender << std::endl;
    outfile.close();
}

void FlightManagementSystem::bookFlight() {
        viewFlights();
        int flightId;
        std::cout << "Enter the flight ID to book: ";
        std::cin >> flightId;

        for (auto& flight : flights) {
            if (flight.id == flightId) {
                if (flight.availableSeats > 0) {
                    std::string departureCity;
                    std::cout << "Enter departure city: ";
                    std::cin >> departureCity;
                    if (!isValidDepartureCity(departureCity)) {
                        std::cout << "Invalid departure city." << std::endl;
                        return;
                    }

                    std::string date, time, name, gender; // Change gender to string
                    int age;
                    std::cout << "Enter date (DD-MM-YYYY): ";
                    std::cin >> date;
                    std::cout << "Enter time from the available times (" << flight.departureTimes << "): ";
                    std::cin >> time;
                    std::cout << "Enter your name: ";
                    std::cin >> name;
                    std::cout << "Enter your age: ";
                    std::cin >> age;
                    std::cout << "Enter your gender (M/F/O): ";
                    std::cin >> gender;

                    flight.availableSeats--;
                    saveBookingDetails(flight, departureCity, date, time, name, age, gender);
                    generateBoardingPass(flight, departureCity, date, time, name, age, gender);
                    std::cout << "Flight booked successfully!" << std::endl;
                    return;
                } else {
                    std::cout << "No available seats on this flight." << std::endl;
                    std::cout << "press enter to continue...";
                    std::cin.ignore();
                    return;
                }
            }
        }
        std::cout << "Flight ID not found." << std::endl;
    }

void FlightManagementSystem::adminLogin() {
    std::string username, password;
    std::cout << "Enter admin username: ";
    std::cin >> username;
    std::cout << "Enter admin password: ";
    std::cin >> password;

    if (username == "admin" && password == "admin123") {
        std::cout << "Admin login successful!" << std::endl;
        isAdmin = true;
    } else {
        std::cout << "Invalid admin credentials." << std::endl;
    }
}

void FlightManagementSystem::userSignup() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    User user(username, password);
    if (user.signup()) {
        currentUser = user;
    }
}

void FlightManagementSystem::userLogin() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    User user(username, password);
    if (user.login()) {
        currentUser = user;
        isAdmin = (username == "admin");
    }
}

void FlightManagementSystem::userLogout() {
    currentUser.logout();
}

void FlightManagementSystem::showAdminMenu() {
    int choice;
    while (true) {
        clear_screen(); // Clear the screen
        std::cout << "\nAdmin Menu:\n";
        std::cout << "1. Add Flight\n2. Add Departure City\n3. View Flights\n4. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addFlight();
                break;
            case 2:
                addDepartureCity();
                break;
            case 3:
                viewFlights();
                std::cout << "press enter to continue...";
                std::cin.ignore();
                break;
            case 4:
                userLogout();
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void FlightManagementSystem::showUserMenu() {
    int choice;
    while (true) {
        clear_screen(); // Clear the screen
        std::cout << "\nUser Menu:\n";
        std::cout << "1. View Flights\n2. Book Flight\n3. View Bookings\n4. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                viewFlights();
                std::cout << "press enter to continue...";
                std::cin.ignore();
                break;
            case 2:
                bookFlight();
                break;
            case 3:
                viewBookings();
                break;
            case 4:
                userLogout();
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void FlightManagementSystem::showInitialMenu() {
    int choice;
    while (true) {
        clear_screen(); // Clear the screen
        std::cout << "\nWelcome to the Flight Management System\n";
        std::cout << "1. Admin Login\n2. User Signup\n3. User Login\n4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                adminLogin();
                if (isAdmin) showAdminMenu();
                break;
            case 2:
                userSignup();
                if (!isAdmin) showUserMenu();
                break;
            case 3:
                userLogin();
                if (isAdmin) showAdminMenu();
                else showUserMenu();
                break;
            case 4:
                exit(0);
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}
