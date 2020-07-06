#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime( long sec) { 
    
    int h = sec/3600;
    int m = (sec - h*3600)/60;
    int s = sec - h*3600 - m*60;
    std::string elapsedTime = TimeToString(h) + ":" + TimeToString(m) + ":" + TimeToString(s);
    return elapsedTime; 
}
string Format::TimeToString(int t){
    
    std::string strg = std::to_string(t);
    while(strg.length() < 2) {
        strg = "0" + strg;
    }

    return strg; 
    
    }