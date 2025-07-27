#ifndef DATABASE_H
#define DATABASE_H



#include<fstream>
#include<algorithm>
#include<sstream>
#include<iomanip>
#include<vector>
#include<string>

using std::string;
using std::vector;

class Database {




public:
    
    Database() noexcept;

    struct Airport {
    string name;
    string id;
    };

    struct Flight {
    string flightId;
    string airline;
    string origin;
    string dest;
    string departureTime;
    int duration;
    float price;
    };

    struct Booking {
    string bookingId;
//    string userId;
    string name;
    string flightId;
    string airline;
    string origin;
    string dest;
    int duration;
    string departureTime;
    string bookingDate;
    string sex;
    string gmail;
    int baggage;
    string mealPreference;
    float cost;
    };

    std::string getAirportID(int index) const;
    void loadAirports();
    void loadFlights();
    vector<std::string> getAirportNames() const;
    vector<Flight> getFlights(const std::string& origin, const std::string& dest) const;
    void saveBooking(const Booking& booking);
    string generateBookingID();


private:
    vector<Airport> airports;
    vector<Flight> flights;
    vector<Booking> bookings;
    string airportsFile;
    string flightFile;
    string bookingsFile;       
    int bookingCounter;     //to generate unique booking ID;

};
      







#endif




