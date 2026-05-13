#include <iostream>
#include <stdexcept>
#include "weight.hpp"

double weight::toGrams(double w, weight_unit y){
    double res = 0;

    if(w < 0){
        throw std::invalid_argument("[SYSTEM] invalid negative mass");
    }

    switch (y){
        case kilograms:
            std::cout<<"From kilos to grams"<<std::endl;
            res = w * 1000.0;
            break;
        case ounces:
            std::cout<<"From ounces to grams"<<std::endl;
            res = w * 28.3495;
            break;
        case pounds:
            std::cout<<"From pounds to grams"<<std::endl;
            res = w * 453.592;
            break;
        case stones:
            std::cout<<"From stones to grams"<<std::endl;
            res = w * (453.592 * 14);
            break;
        default:
            std::cout<<"Already in grams, or invalid operation!"<<std::endl;
            res = w;
    }
    return res; 
}

double weight::toKilos(double w, weight_unit y){
    double res = 0;

    if(w < 0){
        throw std::invalid_argument("[SYSTEM] invalid negative mass");
    }

    switch (y){
        case grams:
            std::cout<<"From grams to kilos"<<std::endl;
            res = w / 1000;

            break;

        case kilograms:{
            static int tentativi = 0;
            int answer;

            std::cout<<"[SYSTEM] Already in kilos!"<<std::endl;
            std::cout<<"Try, 0 - [grams], 2 - [ounces], 3 - [pounds], 4 - [stones]"<<std::endl;

            std::cin>>answer;
            tentativi++;

            if(tentativi > 3){
                std::cout<<"[SYSTEM] converting to grams <default action>"<<std::endl;
                tentativi = 0;
                return toGrams(w, kilograms);
            }
                
            weight_unit y_nuovo = static_cast<weight_unit>(answer);

            if(y_nuovo != kilograms)
                tentativi = 0;

            return toKilos(w, y_nuovo);

        }
            break;
    
    default:
        std::cout<<"To kilos via grams"<<std::endl;
        
        res = toGrams(w, y);

        res = toKilos(res, grams);

        break;
    }
    return res;
}

double weight::toOunches(double w, weight_unit y){
    double res = 0;

    if(w < 0){
        throw std::invalid_argument("[SYSTEM] invalid negative mass");
    }

    switch(y){
        case grams:
            std::cout<<"From grams to ounces"<<std::endl;
            res = w / 28.3495;
            break;
        
        case ounces:{
            static int tentativi = 0;
            int answer;

            std::cout<<"[SYSTEM] Already in ounces"<<std::endl;
            std::cout<<"Try, 0 - [grams], 1 - [kilograms], 3 - [pounds], 4 - [stones]"<<std::endl;

            std::cin>>answer;
            tentativi++;

            if(tentativi > 3){
                std::cout<<"[SYSTEM] converting to grams <default action>"<<std::endl;
                tentativi = 0;
                return toGrams(w, ounces);
            }

            weight_unit y_nuovo = static_cast<weight_unit>(answer);

            if(y_nuovo != ounces)
                tentativi = 0;
            
            return toOunches(w, y_nuovo);

        }
        break;

        default:
            std::cout<<"[SYSTEM] to ounches via grams"<<std::endl;

            res = toGrams(w, y);
            res = toOunches(res, grams);

            break;
    }
    return res;
}

double weight::toPounds(double w, weight_unit y){
    double res = 0;

    if(w < 0){
        throw std::invalid_argument("[SYSTEM] invalid negative mass");
    }

    switch (y){
        case grams:
            std::cout<<"[SYSTEM] from grams to pounds"<<std::endl;
            res = w / 453.592;
            break;
        case pounds:{
            std::cout<<"[SYSTEM] already in pounds"<<std::endl;
            std::cout<<"Try, 0 - [grams], 1 - [kilograms], 3 - [ounces], 4 - [stones]"<<std::endl;

            static int tentativi = 0;
            int answer;
            std::cin>>answer;
            tentativi++;
            
            if(tentativi > 3){
                std::cout<<"[SYSTEM] converting to grams <default action>"<<std::endl;
                tentativi = 0;
                return toGrams(w, y);
            }

            weight_unit y_nuovo = static_cast<weight_unit>(answer);

            if(y_nuovo != pounds)
                tentativi = 0;

            return toPounds(w, y_nuovo);
        }
            break;
    
        default:
            std::cout<<"To pounds via grams"<<std::endl;

            res = toGrams(w,y);

            res = toPounds(res, grams);

            break;
    }
    return res;
}

double weight::toStones(double w, weight_unit y){
    double res = 0;

    if(w < 0){
        throw std::invalid_argument("[SYSTEM] invalid negative mass");
    }

    switch(y){
        case grams:
            std::cout<<"[SYSTEM] from grams to stones"<<std::endl;
            res = w / (453.592 * 14);
            break;

        case stones:{
            std::cout<<"[SYSTEM] Already to stones"<<std::endl;;
            std::cout<<"Try: 0 - [grams], 1 - [kilograms], 2 - [ounces], 3 - [pounds]"<<std::endl;

            static int tentativi = 0;
            int answer;
            std::cin>>answer;
            tentativi++;

            if(tentativi > 3){
                std::cout<<"[SYSTEM] converting to grams <default action>"<<std::endl;
                tentativi = 0;
                return toGrams(w,y);
            }

            weight_unit y_nuovo = static_cast<weight_unit>(answer);

            if(y_nuovo != stones)
                tentativi = 0;

            return toStones(w, y_nuovo);
        }
            break;

        case pounds:
            std::cout<<"[SYSTEM] from stones to punds"<<std::endl;
            res = w / 14.0;

            break;
        
        default:
            std::cout<<"To stones via grams"<<std::endl;

            res = toGrams(w,y);

            res = toStones(res, grams);

            break;
    }
    return res;
}

