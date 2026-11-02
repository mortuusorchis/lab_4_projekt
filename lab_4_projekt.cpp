#include <iostream>
#include <cmath>
using namespace std;

void showPopulation(); // prototyp funkcji showPopulation
void simulateDay(); // prototyp funkcji simulateDay
int susceptible = 80;
int infected = 10;
int recovered = 10;
int day = 0;

double infectionRate = 0.20; 
double recoveryRate = 0.10; // parametry modelu

int main() {
	
	
	int choice;
	bool running = true;

	
	while (running) {

		showPopulation();

		cout << "=== Epidemic Simulator ===" << endl;
		cout << "1. Simulate next day " << endl;
		cout << "2. Change model parameters " << endl;
		cout << "3. Exit " << endl;
		cout << "Yor choice: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 1: { // stymulacja tylko dla jednego kolejnego dnia
			day++;

			

			int NewInfected = infected * infectionRate;
			int NewRecovered = recovered * recoveryRate;

			if (NewInfected > susceptible) { // zabezpieczenie przed ujemną liczbą podatnych na zakażenie, która wystąpiłaby gdy zakażeni > podatnych
				NewInfected = susceptible;
			}

			susceptible = susceptible - NewInfected;
			infected = infected + NewInfected;
			recovered = recovered + static_cast<int>(NewRecovered);

			cout << "*** Simulated day " << day << "***" << endl;
			break;
		}
		case 2: { // zmiana parametrów modelu
			cout << "Change the infection rate, choose from the rage from 0.00 to 1.00:  ";
			cin >> infectionRate;
			cout << "Change the recovery rate, chose from the rage from 0.00 to 1.00: ";
			cin >> recoveryRate;
			cout << "Your parameters have been successfully updated" << endl;
			break;
		}
		case 3: { // kontrolowane zakończenie programu
			cout << "Exiting simutator. Bye :)" << endl;

			running = false;
			break;
		}
		default: {
			cout << "error: invalid command. please try again.";
			break;
		}
		}
	
	}
	

		return 0;

  }
 
void showPopulation() { // definicja funkcji showPopulation

	cout << "Day: " << day << endl;
	cout << "Susceptible: " << susceptible << endl;
	cout << "Infected: " << infected << endl;
	cout << "Recovered: " << recovered << endl;
	cout << "Total: " << susceptible + infected + recovered << endl;
	cout << endl;
}

void simulateDay() {

	int InfectedAtStart = infected;

	int NewInfected =  floor(InfectedAtStart *  infectionRate);
	int NewRecovered = floor(InfectedAtStart * recoveryRate);

	if (NewInfected > susceptible) {
		NewInfected = susceptible;
	}
	if (NewRecovered > InfectedAtStart) {
		NewRecovered = InfectedAtStart;
	}
	susceptible = susceptible - NewInfected;
	infected = infected + NewInfected - NewRecovered;
	recovered = recovered + NewRecovered;

	day++;

	cout << "*** Simulated day " << day << " ***" << endl;
}
