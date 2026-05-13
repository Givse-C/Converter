enum weight_unit {
    grams,      // Base metrica
    kilograms,  // Base metrica
    ounces,     // Imperiale
    pounds,     // Imperiale
    stones      // Imperiale (UK)
};

class weight{
    private:
        double w;
    
    public:
        double toGrams(double w, weight_unit y);
        double toKilos(double w, weight_unit y);
        double toOunches(double w, weight_unit y);
        double toPounds(double w, weight_unit y);
        double toStones(double w, weight_unit y);
};