#include <iostream>
#include "model/Rent.h"

using namespace boost::local_time;
using namespace boost::posix_time;
using namespace std;

int main() {
    Client k1("Waldemar","Nowak","92875697851", "Warszawska", "22","Batorego","55G");
    Client k2("Jan","Kowalski","87110701881","Spokojna","1","Głośna","12");
    Vehicle vehicle1("WW5698",180);
    Vehicle vehicle2("PO9258",140);
    time_zone_ptr zone(new posix_time_zone("CET"));
    local_date_time *rentalDateTime1 = new local_date_time(local_sec_clock::local_time(zone)-hours(51));
    //local_date_time *rentalDateTime2 = new local_date_time(local_sec_clock::local_time(zone)-hours(258));
    Rent rent1(rentalDateTime1,&k1,&vehicle1);
    Rent rent2(&k2,&vehicle2);
    cout<<rent1.rentInfo()<<endl;
    cout<<rent2.rentInfo()<<endl;
    rent1.returnVehicle();
    cout<<rent1.rentInfo()<<endl;
    return 0;
}