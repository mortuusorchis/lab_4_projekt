#include <iostream>
#include <cmath>
using namespace std;

void showPopulation(int day, int susceptible, int infected, int recovered); // prototyp funkcji showPopulation
void simulateDay(); // prototyp funkcji simulateDay
bool checkPopulation(int susceptible, int infected, int recovered); // prototyp funkcji checkPopulation
void showHistory();

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

	populationHistory[0][0] = susceptible;
	populationHistory[0][1] = infected;
	populationHistory[0][2] = recovered;

	int choice;
	bool running = true;


	while (running) {
		
		showPopulation(day, susceptible, infected, recovered); // wyświetlanie populacji przed menu (krok 3)

		cout << "=== Epidemic Simulator ===" << endl;
		cout << "1. Simulate next day " << endl;
		cout << "2. Change model parameters " << endl;
		cout << "3. Exit " << endl;
		cout << "4. Show simulation history " << endl;
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
					populationHistory[day][0] = susceptible;
					populationHistory[day][1] = infected;
					populationHistory[day][2] = recovered;
				}
			}
			else {
				cout << "You have reached the maximum number of days" << endl;
			
			}	
		break;
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

		case 4: {
			showHistory();
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

	////////////////////
	if (infected > 0 && NewRecovered == 0) { // pętla zabezpiecza przed tym, że 0 osób wyzdrowiało kiedy infected> 0 
		                                     // bez tej pętli program czesto daje 0 osób, które zdrowieją przed osiągnęciem 100 dni
		NewRecovered = 1;     
	}
	//////////////////// // kod zapisany pomiedzy ////... i ////... nie jest konieczny do prawidłowego działania programu
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

void showHistory() {
	for (int i = 0; i <= day; i++) {
		
		cout << "Day " << i << endl;
		cout << "Susceptible: " << populationHistory[i][0] << endl;
		cout << "Infected: " << populationHistory[i][1] << endl;
		cout << "Recovered: " << populationHistory[i][2] << endl;

		if (i == 0) {
			cout << "New infections: - " << endl;
			cout << "New recoveries: - " << endl;
		}
		else {
			cout << "New infections: " << dailyNewInfections[i - 1] << endl;
			cout << "New recoveries: " << dailyRecoveries[i - 1] << endl;
		}
		cout << endl;
	}
}
