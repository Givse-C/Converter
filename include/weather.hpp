enum temp{
    celsius,    //0
    fahrenheit, //1
    kelvin      //2
};

class meteo{
    private:
        double x;
        bool validInput(double x, temp y);
    
    public:
        double toCelsius(double x, temp y);
        double toFahrenheit(double x, temp y);
        double toKelvin(double x, temp y);
};