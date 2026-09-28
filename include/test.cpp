#include <iostream>
#include "history.hpp"


int main(){
    queue<std::string> res;
    res.add(7.5, "fahrenheit");
    res.add(7, "kelvin");
    res.add(0, "meters");
    res.add(11, "pounds");
    res.add(11, "pounds");
    res.add(11, "pounds");
    res.add(11, "pounds");
    res.add(11, "pounds");
    res.add(11, "pounds");
    res.add(11, "pounds");
    //res.add(11, "pounds");

    std::cout<<"Ultimo elemento"<<std::endl;
    auto[valore, unità] = res.get_top();
    std::cout<<valore<<unità<<std::endl;
    std::cout<<std::endl;

    std::cout<<"before clearing"<<std::endl;
    res.print();

    std::cout<<"after clearing"<<std::endl;
    //res.clear();
    res.print();

    //file
    try{
        res.save_to_file("test.txt");
    }catch(const std::exception& e){
        std::cout<<"ERRORE"<<std::endl;
    }
    

    

    return 0;

}