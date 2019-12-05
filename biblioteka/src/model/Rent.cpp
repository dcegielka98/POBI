//
// Created by student on 09.11.2019.
//

#include "model/Rent.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "model/Vehicle.h"
#include "model/Client.h"
#include "model/RentsRepository.h"

using namespace std;
using namespace boost::uuids;
using namespace boost::local_time;
using namespace boost::posix_time;

Rent::Rent(local_date_timePtr rentalDateTime, ClientPtr client, VehiclePtr vehicle) : rentalDateTime(
        rentalDateTime), client(client), vehicle(vehicle), uuid(random_generator()()), rentPrice(0.0) {}

Rent::~Rent() = default;

int Rent::rentDuration() const {
    if(returnDateTime) {
        local_time_period duration(*rentalDateTime, *returnDateTime);
        if (duration.length().hours() % 24 == 0) return duration.length().hours() /24;
        else return (duration.length().hours() /24) + 1;
    }
    else return 0;
}

string Rent::rentClientInfo() const{
    return client->clientInfo();
}

string Rent::rentVehicleInfo() const{
    return vehicle->vehicleInfo();
}

string Rent::rentInfo() const{
    string info;
    info.append("ID wypożyczenia: ").append(to_string(uuid))
            .append("\nData wypożyczenia: ").append(rentalDateTime->to_string())
            .append("\nIlość dni wypożyczenia: ").append(to_string(rentDuration()));
    if(returnDateTime != nullptr){
        info.append("\nData zwrotu: ").append(returnDateTime->to_string())
                .append("\nKoszt wypożyczenia: ").append(to_string(rentPrice));
    }
    info.append("\nWypożyczony pojazd\n").append(rentVehicleInfo())
            .append("\nOsoba wypożyczająca\n").append(rentClientInfo());
    return info;
}

void Rent::returnVehicle() {
    time_zone_ptr zone(new posix_time_zone("CET"));
    returnDateTime = make_shared<local_date_time>(local_sec_clock::local_time(zone));
    rentPrice = vehicle->actualRentalPrice() * rentDuration();
    rentPrice -= client->getClientDiscount(rentPrice);
}

const ClientPtr &Rent::getClient() const {
    return client;
}

const VehiclePtr &Rent::getVehicle() const {
    return vehicle;
}

double Rent::getRentPrice() const {
    return rentPrice;
}
