#include "City.h"

City::City(const std::string& name, const std::string& airportCode)
    : name(name), airportCode(airportCode) {}

std::string City::getName() const {
    return name;
}

std::string City::getAirportCode() const {
    return airportCode;
}
