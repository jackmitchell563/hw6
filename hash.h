#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
      // Add your code here
      unsigned long long curr = 0;
      unsigned long long w[5] = {0, 0, 0, 0, 0};
      int numgroups = 0;
      for(int i = 0; i < k.length(); i++){
        curr *= 36;
        curr += letterDigitToNumber(k[i]);
        if((k.length() - i - 1) % 6 == 0){ // breakpoint for group of 6
          w[i / 6] = curr; // note: fills in w starting from 0, so need to reorder later
          curr = 0; // reset current value for new group
          numgroups++; // necessary for reordering
        }
      }
      for(int i = numgroups - 1; i >= 0; i--){ // shifts w values to be right-aligned (at w[4])
        w[i + 5 - numgroups] = w[i];
      }
      for(int i = 0; i < 5 - numgroups; i++){ // clears leftover values from above shift
        w[i] = 0;
      }
      return rValues[0] * w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4] * w[4];
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
      // Add code here or delete this helper function if you do not want it
      if(letter >= 'A' and letter <= 'Z') letter -= ('A' - 'a'); // convert A-Z to a-z
      if(letter >= 'a' and letter <= 'z') return letter - 'a';
      else if(letter >= '0' and letter <= '9') return 26 + letter - '0';
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
