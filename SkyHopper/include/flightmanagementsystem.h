#include "flight.h"
#include <vector>
#include "user.h"
#ifndef FLIGHTMANAGEMENTSYSTEM_H
#define FLIGHTMANAGEMENTSYSTEM_H

class FlightManagementSystem {
private:
    std::vector<Flight> flights;
    User currentUser;
    bool isAdmin;

public:
    FlightManagementSystem() : isAdmin(false) {
        loadFlights();
    }

    void generateBoardingPass(const Flight& flight, const std::string& departureCity, const std::string& date, const std::string& time, const std::string& name, int age, const std::string& gender);
    void saveBookingDetails(const Flight& flight, const std::string& departureCity, const std::string& date, const std::string& time, const std::string& name, int age, const std::string& gender);
    bool isValidDepartureCity(const std::string& city);
    void bookFlight();
    void loadFlights();
    void addFlight();
    void addDepartureCity();
    void viewBookings();
    void viewFlights();
    void adminLogin();
    void userSignup();
    void userLogin();
    void userLogout();
    void showAdminMenu();
    void showUserMenu();
    void showInitialMenu();
};

#endif // FLIGHTMANAGEMENTSYSTEM_H
