#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include "weather.hpp"
#include "weight.hpp"
#include "distances.hpp"

//-------------handlers------------------
void meteo_handler();
void weight_handler();
void dist_handler();
//-------------in words------------------
std::string numbersToWords(long long n);


std::string lower(std::string& s){
    char c;
    if(s.empty())
        throw ("string is empty");

    for(int i = 0; i < s.length() ; i++){
        c = std::tolower(s.at(i));
        s.at(i) = c;
    }
    return s;
}

int main(){
    std::cout<<"[SYSTEM] Welcome to unit conveter module "<<std::endl;
    std::cout<<"Choose the convertion [weather], [weight], [distance]"<<std::endl;
    std::string input = "[";

    std::string answer;
    std::cin>>answer;
    
    lower(answer);
    
    input += answer;
    input += "]";

    if(answer.find("weat") != std::string::npos){
        std::cout<<"Weather confirmed"<<std::endl;
        meteo_handler();  
    }
    else if(answer.find("weig") != std::string::npos){
        std::cout<<"Weight confirmed"<<std::endl;
        weight_handler();
    }
    else if(answer.find("dist") != std::string::npos){
        std::cout<<"Distance confirmed"<<std::endl;
        dist_handler();
    }
    else{
        throw std::invalid_argument("[CRITICAL] invalid input");
    }
    
    return 0;
}
//helpers
std::string numbersToWords(long long n){
    static const std::vector<std::string> ones = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    static const std::vector<std::string> tens = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    if(n == 0){
        return "zero";
    }
    else if(n < 0){
        return "minus" + numbersToWords(-n);
    }
    else{
        std::string res = "";

        if (n >= 1000000000000LL) {
            res += numbersToWords(n / 1000000000000LL) + " trillion ";
            n %= 1000000000000LL;
        }
        if(n >= 1000000000LL){
            res += numbersToWords(n / 1000000000) + " bilion ";
            n %= 1000000000;
        }
        if(n >= 1000000){
            res += numbersToWords(n / 1000000000) + " milion ";
            n %= 1000000;
        }
        if( n >= 1000){
            res += numbersToWords(n/1000) + " thousand ";
            n %= 1000;
        }
        if (n >= 100) {
            res += numbersToWords(n / 100) + " hundred ";
            n %= 100;
        }
        if (n >= 20) {
            res += tens[n / 10];
            if (n % 10 != 0) {
                res += "-" + ones[n % 10];
            }
        } else if (n > 0) {
            res += ones[n];
        }
    return res;
    }
}


//************************************************************* */
//HANDLERS


void meteo_handler(){
    meteo conv;
    char c_from, c_to;
    double value, res = 0;
    
    // 1. Input Unità di partenza
    std::cout << "[SYSTEM] Choose starting unit? [f/c/k]: ";
    std::cin >> c_from;
    
    // Convertiamo il carattere nell'enum del tuo modulo meteo
    temp unit_from;
    if(c_from == 'f') unit_from = fahrenheit;
    else if(c_from == 'c') unit_from = celsius;
    else unit_from = kelvin;

    // 2. Input Unità di destinazione
    std::cout << "[SYSTEM] Choose destinatinon unit? [f/c/k]: ";
    std::cin >> c_to;


    // 3. Valore
    std::cout << "[SYSTEM] Value: ";
    std::cin >> value;

    try {
        // 4. Logica di conversione
        if(c_to == 'f' || c_to == 'F'){
            res = conv.toFahrenheit(value, unit_from); // Uso unit_from!
        }
        else if(c_to == 'c' || c_to == 'C'){
            res = conv.toCelsius(value, unit_from);
        }
        else if(c_to == 'k' || c_to == 'K'){
            res = conv.toKelvin(value, unit_from);
        }
        else {
            std::cout << "[ERROR] Invalid argument." << std::endl;
            return;
        }

        // 5. Output finale (Fondamentale!)
        std::cout << "------------------------------------" << std::endl;
        std::cout << "[SYSTEM] RESULTS: " << res << std::endl;
        std::cout << "------------------------------------" << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "[ALERT] Invalid argument" << e.what() << std::endl;
    }
}

void weight_handler() {
    weight conv;
    char c_from, c_to;
    double value, res = 0;

    std::cout << "[WEIGHT SYSTEM] Select starting unit:" << std::endl;
    std::cout << "[g] grams | [k] kilograms | [o] ounces | [p] pounds | [s] stones" << std::endl;
    std::cin >> c_from;

    // Mapping del carattere all'enum weight_unit
    weight_unit unit_from;
    switch (tolower(c_from)) {
        case 'g': unit_from = grams; break;
        case 'k': unit_from = kilograms; break;
        case 'o': unit_from = ounces; break;
        case 'p': unit_from = pounds; break;
        case 's': unit_from = stones; break;
        default: 
            std::cout << "[ERROR] Invalid unit." << std::endl;
            return;
    }

    std::cout << "[SYSTEM] select destination unit: ";
    std::cin >> c_to;

    std::cout << "[STIVA] Select weight: ";
    std::cin >> value;

    try {
        // Logica di conversione basata sulla destinazione scelta
        std::cout<<"*****OPERATION LOG*****"<<std::endl;
        switch (tolower(c_to)) {
            case 'g':
                res = conv.toGrams(value, unit_from);
                break;
            case 'k':
                res = conv.toKilos(value, unit_from);
                break;
            case 'o':
                res = conv.toOunches(value, unit_from); // Mantengo il tuo typo 'toOunches'
                break;
            case 'p':
                res = conv.toPounds(value, unit_from);
                break;
            case 's':
                res = conv.toStones(value, unit_from);
                break;
            default:
                std::cout << "[ERROR] Invalid destination UNIT." << std::endl;
                return;
        }

        std::cout << "------------------------------------" << std::endl;
        std::cout << "[WEIGHT] RESULTS: " << res << " " << c_to << std::endl;
        std::cout << "------------------------------------" << std::endl;

    } catch (const std::invalid_argument& e) {
        // Qui catturiamo l'eccezione se il peso è negativo
        std::cerr << "[WEIGHT SYSTEM] Invalid argument" << e.what() << std::endl;
    }
}

void dist_handler() {
    dist conv;
    char c_from, c_to;
    double value, res = 0;
    bool success = false;

    std::cout << "[NAVIGATION SYSTEM] Select starting unit:" << std::endl;
    std::cout << "[m] meters | [k] kilometers | [i] miles | [a] AU | [l] lightyears" << std::endl;
    std::cin >> c_from;

    // Mapping del carattere all'enum dist_unit
    dist_unit unit_from;
    switch (tolower(c_from)) {
        case 'm': unit_from = meters; break;
        case 'k': unit_from = kilometers; break;
        case 'i': unit_from = miles; break;
        case 'a': unit_from = au; break;
        case 'l': unit_from = lightyear; break;
        default: 
            std::cout << "[ERROR] Unrecognised dist unit." << std::endl;
            return;
    }

    std::cout << "[NAVIGATION SYSTEM] select destination unit: ";
    std::cin >> c_to;

    static int tries = 0;

    do{
        std::cout << "[NAVIGATION SYSTEM] select distance: ";
        if(std::cin >> value){
            success = true;
            tries = 0;
        }
        else{
            tries++;
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            if(tries == 3){
                std::cout<<"Are you stupid"<<std::endl;
            }
            else if(tries >= 4){
                tries = 0;
                throw std::invalid_argument("EXCESS OF STUPIDITY");
            }
        }
   
    }while(!success);

    try {
        // Logica di conversione basata sulla destinazione scelta
        std::cout<<std::endl;
        std::cout<<"-----OPERATION LOG-----"<<std::endl;
        switch (tolower(c_to)) {
            case 'm':
                res = conv.toMeters(value, unit_from);
                break;
            case 'k':
                res = conv.toKilometers(value, unit_from);
                break;
            case 'i':
                res = conv.toMiles(value, unit_from);
                break;
            case 'a':
                res = conv.toAU(value, unit_from);
                break;
            case 'l':
                res = conv.toLightYears(value, unit_from);
                break;
            default:
                std::cout << "[ERROR] Invalid unit." << std::endl;
                return;
        }

        std::cout << "------------------------------------------" << std::endl;
        std::cout << "[SYSTEM] RESULTS: " << res << " " << c_to << std::endl;
        std::cout << "Value in scientific notation: " << std::scientific << std::setprecision(4) << res << c_to <<std::endl;
        std::cout << "Value in NON scientific notation: " << std::fixed << std::setprecision(10) << res << c_to <<std::endl;
        std::cout << "Value in characters: " << numbersToWords(res) << c_to <<std::endl;
        std::cout << "------------------------------------------" << std::endl;

    } catch (const std::invalid_argument& e) {
        // Cattura distanze negative (impossibili nello spazio euclideo)
        std::cerr << "[ALERT] invalid argument " << e.what() << std::endl;
    }
}