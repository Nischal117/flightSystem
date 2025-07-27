
#ifndef SIGNUP_H
#define SIGNUP_H

#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdbool.h>
#include <map>
#include <sstream>
#include <fstream>



using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::map;
using std::stringstream;



class SignUp {
 private:
    std::string username = "";
    std::string password = "";
    std::string gmail = "";


 public:
    string getUsername() const{ return username; }
    string getGmail() const{ return gmail; }
    string getPassword() const {return password; }
    bool showSignUp(const vector<string>& options);
    bool findDuplicate();
 // void display();
};
    
//bool showSignUp(const vector<string>& options);

    

   


#endif
