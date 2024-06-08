
#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <vector>
#include "user.h"


class Flight {
    public:
        int id;
        std::string destination;
        std::string departureTimes;
        int availableSeats;

        Flight(int id, std::string destination, std::string departureTimes, int availableSeats);
        void saveToFile();
};

#endif // FLIGHT_H
