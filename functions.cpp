#include "functions.h"

#include <cmath>
#include <string>

typedef char DNA;

std::string convertToBinary(DNA decimal){
    std::string binary;
    if(decimal < 0){
        binary += "1";
        decimal = std::abs(decimal);
    }else{
        binary += "0";
    }
    for(int i = 6; i >= 0; i--){
        if(decimal - std::pow(2, i) >= 0){
            binary += "1";
            decimal -= std::pow(2, i);
        }else{
            binary += "0";
        }
    }
    return binary;
}
char convertFromBinary(std::string binary){
    char decimal = 0;
    // Only dealing with the first 8 characters
    for(unsigned int i = 1; i < 8; i++){
        if(binary.at(i) == '1'){
            decimal += std::pow(2, 7-i);
        }
    }
    if(binary.at(0) == '1'){
        decimal = -std::abs(decimal);
    }
    return decimal;
}
