#include "Booking.h"

Booking::Booking(const std::string& name, const std::string& surname, const std::string& personalID,
                 const std::string& departure, const std::string& arrival, const std::string& date,
                 const std::string& time, const std::string& gateNumber, const std::string& flightNumber,
                 const std::string& seatNumber)
        : name(name), surname(surname), personalID(personalID), departure(departure), arrival(arrival),
          date(date), time(time), gateNumber(gateNumber), flightNumber(flightNumber), seatNumber(seatNumber) {}

std::string Booking::getName() const {
    return name;
}

std::string Booking::getSurname() const {
    return surname;
}

std::string Booking::getPersonalID() const {
    return personalID;
}

std::string Booking::getDeparture() const {
    return departure;
}

std::string Booking::getArrival() const {
    return arrival;
}

std::string Booking::getDate() const {
    return date;
}

std::string Booking::getTime() const {
    return time;
}

std::string Booking::getGateNumber() const {
    return gateNumber;
}

std::string Booking::getFlightNumber() const {
    return flightNumber;
}

std::string Booking::getSeatNumber() const {
    return seatNumber;
}
