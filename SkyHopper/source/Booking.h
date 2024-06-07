#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
public:
    Booking(const std::string& name, const std::string& surname, const std::string& personalID,
            const std::string& departure, const std::string& arrival, const std::string& date,
            const std::string& time, const std::string& gateNumber, const std::string& flightNumber,
            const std::string& seatNumber);

    std::string getName() const;
    std::string getSurname() const;
    std::string getPersonalID() const;
    std::string getDeparture() const;
    std::string getArrival() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getGateNumber() const;
    std::string getFlightNumber() const;
    std::string getSeatNumber() const;

private:
    std::string name;
    std::string surname;
    std::string personalID;
    std::string departure;
    std::string arrival;
    std::string date;
    std::string time;
    std::string gateNumber;
    std::string flightNumber;
    std::string seatNumber;
};

#endif // BOOKING_H
