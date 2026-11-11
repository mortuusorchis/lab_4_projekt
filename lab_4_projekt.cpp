#include <iostream>
#include <cmath>
using namespace std;

void showPopulation(int day, int susceptible, int infected, int recovered); // prototyp funkcji showPopulation
void simulateDay(); // prototyp funkcji simulateDay
bool checkPopulation(int susceptible, int infected, int recovered); // prototyp funkcji checkPopulation

int populationHistory[101][3]; // dni od 0 - 100; 3 rodzaje ludzi: podatni, chorzy, zdrowi
int dailyNewInfections[100] = {};
int dailyRecoveries[100] = {};


// zmienne globalne stanu populacji
int susceptible = 80;
int infected = 10;
int recovered = 10;
int day = 0;

// parametry modelu
double infectionRate = 0.20; 
double recoveryRate = 0.10; 

	
int main() {

	populationHistory[0][0] = 80;
	populationHistory[0][1] = 10;
	populationHistory[0][2] = 10;

	int choice;
	bool running = true;


	while (running) {
		
		showPopulation(day, susceptible, infected, recovered); // wyświetlanie populacji przed menu (krok 3)

		cout << "=== Epidemic Simulator ===" << endl;
		cout << "1. Simulate next day " << endl;
		cout << "2. Change model parameters " << endl;
		cout << "3. Exit " << endl;
		cout << "Your choice: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 1: { 

			if (day < 100) {

				simulateDay();

				if (!checkPopulation(susceptible, infected, recovered)) {
					running = false;
				}
				else {
					cout << "You have reached the maximum number of days" << endl;
				}
				break;
			}
		}
		case 2: { // zmiana parametrów modelu
			double NewInfectionRate, NewRecoveryRate;
			cout << "Change the infection rate, choose from the rage from 0.00 to 1.00:  ";
			cin >> NewInfectionRate;

			cout << "Change the recovery rate, chose from the rage from 0.00 to 1.00: ";
			cin >> NewRecoveryRate;

			if (NewInfectionRate >= 0.00 && NewInfectionRate <= 1.00 && NewRecoveryRate >= 0.00 && NewRecoveryRate <= 1.00) {
				infectionRate = NewInfectionRate;
				recoveryRate = NewRecoveryRate;
				cout << "Your parameters have been successfully updated" << endl;
			}
			else {
				cout << "Error: Invalid values! Paremeters remain unchanged. " << endl;
			}
			cout << endl;
			break;
		}

		case 3: { // kontrolowane zakończenie programu
			cout << "Exiting simutator. Bye :)" << endl;

			running = false;
			break;
		}
		default: {
			cout << "Error: invalid command. please try again." << endl;
			break;
		}
    }
}
return 0;
}

 
void showPopulation(int day, int susceptible, int infected, int recovered) { // definicja funkcji showPopulation

	cout << "Day: " << day << endl;
	cout << "Susceptible: " << susceptible << endl;
	cout << "Infected: " << infected << endl;
	cout << "Recovered: " << recovered << endl;
	cout << "Total: " << susceptible + infected + recovered << endl;
	cout << endl;
}

void simulateDay() {
	
	int InfectedAtStart = infected;

	int NewInfected = static_cast<int>(floor(InfectedAtStart *  infectionRate));
	int NewRecovered = static_cast<int>(floor(InfectedAtStart * recoveryRate));

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

	dailyNewInfections[day - 1] = NewInfected;
	dailyRecoveries[day - 1] = NewRecovered;

	cout << "*** Simulated day " << day << " ***" << endl;
}

bool checkPopulation(int susceptible, int infected, int recovered) {
	if (susceptible >= 0 && infected >= 0 && recovered >= 0 && (susceptible + infected + recovered == 100)) {
		return true;
	}
	else {
		cout << "Error. Something is wrong with your population. " << endl;
		return false;
	}
} 

