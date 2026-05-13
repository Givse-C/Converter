#include <iostream>
#include "distances.hpp"

double dist::toMeters(double d, dist_unit y){
    std::cout <<"[SYSTEM] To meters confirmed" <<std::endl;
    //Converting to meters
    double res = 0;

    if(d < 0)
        throw std::invalid_argument("[SYSTEM] negative distance detected");

    switch (y){
        case meters:
            //returns itself            
            return d;
    
            break;
        case kilometers:
            res = d * 1000;

            break;
        
        case miles:
            res = d * 1609.34;

            break;
        case au:
            res = d * 149597870700.0;

            break;

        case lightyear:
            res = d * 9460730472580800.0;

            break;
        default:
            std::cout<<"[SYSTEM] no more convertion units"<<std::endl;
            break;
    }
    return res;
}

double dist::toKilometers(double d, dist_unit y){
    std::cout<<"[SYSTEM] To kilometers confirmed" <<std::endl;
    double res = 0;
    if(d < 0)
        throw std::invalid_argument("[SYSTEM] negative distance detected");

    switch(y){
        case meters:
            res = d / 1000.0;
            break;
        case kilometers:{
            std::cout<<"[SYSTEM] already to kilometers"<<std::endl;
            std::cout<<"[SYSTEM] try : [0] - meters | [2] - miles | [3] - Astronomical Units | [4] - lightyears"<<std::endl;

            static int tentativi = 0;
            int answer;
            std::cin>>answer;
            tentativi++;

            if(tentativi == 3){
                std::cout<<"Converting to meters <default action>"<<std::endl;
                tentativi = 0;
                return toMeters(d, kilometers);
            }

            //casting
            dist_unit y_nuovo = static_cast<dist_unit>(answer);

            if(y_nuovo != kilometers){
                tentativi = 0;
            }

            return toKilometers(d, y_nuovo);
        }
            break;

        default:
            res = toMeters(d, y);

            res = toKilometers(res, meters);

            break;

    }
    return res;
}

double dist::toMiles(double d, dist_unit y){
    std::cout << "[SYSTEM] To miles confirmed" << std::endl;
    double res = 0;
    
    // Controllo sicurezza tramite eccezione
    if(d < 0)
        throw std::invalid_argument("[SYSTEM] negative distance detected");

    switch(y){
        case meters:
            // 1 miglio = 1609.34 metri
            res = d / 1609.34;
            break;

        case miles: {
            static int tentativi = 0;
            int answer;

            std::cout << "[SYSTEM] already in miles!" << std::endl;
            std::cout << "[SYSTEM] try: [0]-meters | [1]-kilometers | [3]-AU | [4]-lightyears" << std::endl;

            std::cin >> answer;
            tentativi++;

            if(tentativi >= 3){
                std::cout << "[SYSTEM] too many attempts. Converting to meters <default action>" << std::endl;
                tentativi = 0;
                return toMeters(d, miles);
            }

            dist_unit y_nuovo = static_cast<dist_unit>(answer);

            if(y_nuovo != miles)
                tentativi = 0;

            return toMiles(d, y_nuovo);
        }
        break;

        default:
            // Passo ponte verso l'unità base (metri)
            res = toMeters(d, y);
            // Ricorsione finale: dai metri ottenuti calcolo le miglia
            res = toMiles(res, meters);
            break;
    }
    return res;
}

double dist::toAU(double d, dist_unit y) {
    std::cout << "[SYSTEM] To Astronomical Units confirmed" << std::endl;
    double res = 0;

    // Controllo sicurezza tramite eccezione
    if (d < 0)
        throw std::invalid_argument("[SYSTEM] negative distance detected");

    switch (y) {
        case meters:
            // 1 AU = 149.597.870.700 metri
            res = d / 149597870700.0;
            break;

        case au: {
            static int tentativi = 0;
            int answer;

            std::cout << "[SYSTEM] already in Astronomical Units!" << std::endl;
            std::cout << "[SYSTEM] try: [0]-meters | [1]-kilometers | [2]-miles | [4]-lightyears" << std::endl;

            std::cin >> answer;
            tentativi++;

            if (tentativi >= 3) {
                std::cout << "[SYSTEM] too many attempts. Converting to meters <default action>" << std::endl;
                tentativi = 0;
                // Redirigo ai metri partendo dal valore in AU (d * 149...700)
                return toMeters(d, au);
            }

            dist_unit y_nuovo = static_cast<dist_unit>(answer);

            if (y_nuovo != au)
                tentativi = 0;

            return toAU(d, y_nuovo);
        }
        break;

        default:
            // 1. Convertiamo l'unità ignota (es. miglia o anni luce) in metri
            res = toMeters(d, y);
            // 2. Chiamata ricorsiva finale dai metri alle AU
            res = toAU(res, meters);
            break;
    }
    return res;
}

double dist::toLightYears(double d, dist_unit y){
    std::cout<<"[SYSTEM] to lightyears confirmed" <<std::endl;
    double res = 0;

    // Controllo sicurezza (Eccezione)
    if(d < 0)
        throw std::invalid_argument("[SYSTEM] critical error: negative distance in interstellar space");

    switch(y){
        case meters:
            // 1 ly = 9.460.730.472.580.800 metri (usiamo la costante scientifica)
            res = d / 9460730472580800.0;
            break;

        case lightyear: {
            static int tentativi = 0;
            int answer;

            std::cout << "[SYSTEM] already in Lightyears!" << std::endl;
            std::cout << "[SYSTEM] try: [0]-meters | [1]-kilometers | [2]-miles | [3]-AU" << std::endl;

            std::cin >> answer;
            tentativi++;

            if(tentativi >= 3){
                std::cout << "[SYSTEM] limit reached. Reverting to meters <default action>" << std::endl;
                tentativi = 0;
                return toMeters(d, lightyear);
            }

            dist_unit y_nuovo = static_cast<dist_unit>(answer);

            if(y_nuovo != lightyear)
                tentativi = 0;

            return toLightYears(d, y_nuovo);
        }
        break;

        default:
            // Trasformiamo l'unità di partenza (km, mi, AU) in metri
            res = toMeters(d, y);
            // Ricorsione finale: dai metri agli anni luce
            res = toLightYears(res, meters);
            break;
    }
    return res;
}


