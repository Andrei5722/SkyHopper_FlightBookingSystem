#ifndef FLIGHTBOOKINGSYSTEM_H
#define FLIGHTBOOKINGSYSTEM_H

#include "City.h"
#include "Booking.h"
#include <vector>
#include <string>

class FlightBookingSystem {
public:
    FlightBookingSystem(const std::string& citiesFile);

    void showMainMenu();
    void searchFlights();
    void bookFlight(const std::string& departure, const std::string& arrival, const std::string& date, const std::string& time);
    void printBoardingPass(const Booking& booking);
    void saveCredentials(const std::string& username, const std::string& password);
    bool checkCredentials(const std::string& username, const std::string& password);
    void saveBooking(const std::string& bookingDetails);


    void showBookedFlights();

private:
    void loadCities(const std::string& citiesFile);
    std::vector<City> cities;
    std::vector<Booking> bookings;

    std::string generateGateNumber() const;
    std::string generateFlightNumber() const;
    std::string generateSeatNumber() const;

    std::string loggedInUser;
};

#endif // FLIGHTBOOKINGSYSTEM_H
