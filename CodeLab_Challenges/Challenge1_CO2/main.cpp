#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

double getDistance() {
    double miles;
    while (true) {
        cout << "Enter journey distance in miles: ";
        if (cin >> miles && miles >= 0) return miles;
        cout << "Please enter a valid non-negative number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

char getFuelType() {
    char fuel;
    while (true) {
        cout << "Enter fuel type (D for diesel, P for petrol): ";
        cin >> fuel;
        if (fuel == 'D' || fuel == 'd' || fuel == 'P' || fuel == 'p') return fuel;
        cout << "Please choose D or P.\n";
    }
}

double calculateCO2(double miles, char fuel) {
    const double litresPer100Miles = 9.66;
    double kgPerLitre = (fuel == 'D' || fuel == 'd') ? 2.68 : 2.31;
    return (miles / 100.0) * litresPer100Miles * kgPerLitre;
}

int main() {
    cout << "CO2 Journey Calculator\n";
    double distance = getDistance();
    char fuel = getFuelType();
    cout << fixed << setprecision(2);
    cout << "Estimated CO2 emissions: " << calculateCO2(distance, fuel) << " kg\n";
    return 0;
}
