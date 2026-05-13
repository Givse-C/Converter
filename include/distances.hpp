enum dist_unit {
    meters,      // 0
    kilometers,  // 1
    miles,       // 2
    au,          // 3 (Unità Astronomiche)
    lightyear    // 4 (Anni Luce)
};

class dist{
    public:
        double toMeters(double d, dist_unit y);
        double toKilometers(double d, dist_unit y);
        double toMiles(double d, dist_unit y);
        double toAU(double d, dist_unit y);
        double toLightYears(double d, dist_unit y);
    private:
        bool isValid(double d, dist_unit y);
};