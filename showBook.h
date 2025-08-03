#ifndef SHOWBOOK_H
#define SHOWBOOK_H

#include<fstream>
#include<algorithm>
#include<sstream>
#include<iomanip>
#include<vector>
#include<string>
#include<ncurses.h>
#include<cmath>



using std::string;
using std::vector;



    class showFlight {
    
   
    

    public:
   
    
    struct ticketPg {
    string bookingId;
    string name;
    string flightId;
    string airline;
    string origin;
    string destination;
    string departureDate;
    string departureTime;
    string mealPreference;
    int duration;
    int baggage;
    float cost;

    };

    struct booking{
    string bookId;
    string name;
    string flightId;
    
    string flightDate;
    string departureTime;

    string origin;
    string destination;
         
    };

    
  
  static  string displayUserFlight(const string& gmail);
  static void ticket(const string& bookId);
  static void removeFlight(const string& deleteId);


};




#endif
