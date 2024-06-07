#ifndef CITY_H
#define CITY_H

#include <string>

class City {
public:
    City(const std::string& name, const std::string& airportCode);

    std::string getName() const;
    std::string getAirportCode() const;

private:
    std::string name;
    std::string airportCode;
};

#endif // CITY_H
