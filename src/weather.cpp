#include <iostream>
#include "weather.hpp"

bool meteo::validInput(double x, temp y){
    if(y == 0 && x < -273.15)
        return false;
    if(y == 1 && x <  -459.67)
        return false;
    if(y == 2 && x < 0)
        return false;
    return true;
}
double meteo::toCelsius(double x, temp y){
    double res = 0;

    if(!validInput(x,y)){
        throw std::invalid_argument("[SYSTEM] Too low temperature");
    }

    if(y == 1){
        std::cout<<"Converting from Fahrenheit to Celsius..."<<std::endl;
        res = (x - 32) * (5.0/9.0);
    }
    else if(y == 2){
        std::cout<<"Converting from Kelvin to Celsius..."<<std::endl;
        res = x - 273.15;
    }
    else{
        std::cout<<"[Warning] already in celsius"<<std::endl;
    }
    return res;
}

double meteo::toKelvin(double x, temp y){
    double res = 0;

    if(!validInput(x,y)){
        throw std::invalid_argument("[SYSTEM] Too low temperature");
    }

    if(y == 0){
        std::cout<<"Converting from Celsius to Kelvin..."<<std::endl;
        res = x + 273.15;
    }
    else if(y == 1){
        //K = (°F + 459.67) × 5/9
        std::cout<<"Converting from fahrenheit to kelvin"<<std::endl;
        res = (x + 459.67) * (5.0/9.0);
    }
    else{
        std::cout<<"Warning: already in kelvin"<<std::endl;
    }
    return res;
}

double meteo::toFahrenheit(double x, temp y){
    double res = 0;

    if(!validInput(x,y)){
        throw std::invalid_argument("[SYSTEM] Too low temperature");
    }

    if(y == 0){
        //°F = °C * 1.8 + 32
        std::cout<<"From celsius to fahrenherit..."<<std::endl;
        res = (x * 1.8) + 32.0;
    }

    else if(y == 2){
        //°F = K * 1.8 - 459.67
        std::cout<<"kelvin to fahrenheit"<<std::endl;
        res = x * 1.8 - 459.67;
    }
    return res;
}

