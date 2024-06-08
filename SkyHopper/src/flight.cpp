
#include "../include/flight.h"
#include <iostream>
#include <fstream>

Flight::Flight(int id, std::string destination, std::string departureTimes, int availableSeats)
    : id(id), destination(destination), departureTimes(departureTimes), availableSeats(availableSeats) {}

void Flight::saveToFile() {
    std::ofstream outfile("../data/flights.txt", std::ios::app);
    outfile << id << " " << destination << " " << departureTimes << " " << availableSeats << std::endl;
    outfile.close();
}
