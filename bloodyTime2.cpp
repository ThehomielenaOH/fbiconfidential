#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Created a data structure called period to store it's date and length
struct period {
    int year;
    int month;
    int day;
    int length;
};

//Takes input from user and stores the period data in a period variable
void recordPeriod(period blood) {
    cout << "Enter the year, month, date, and length (in days) of your period seperated by a space: ";
    cin >> blood.year >> blood.month >> blood.day >> blood.length;
}

//Prints period data to console in an easily readable format
void printPeriod (period blood) {
    cout << blood.month << "/" << blood.day << "/" << blood.year << " " << blood.length << " days" << endl;
}

//goes through all periods in a vector and calculates average length of menstruation
int findAverageCycle (vector<period> periods) {
    int sum = 0;
    int average = 0;
    int n = periods.size();
    for (int i = 0; i < n; i++) {
        sum += periods[i].length;
    }
    average = sum / n;
    return average;
}

int main() {
    //Declare period vector, menu option integer, and other variables
    vector<period> allPeriods;
    int desiredAction = 1;
    period tempPeriod;
    int avgCycleLength;
    
    //Create variables for file stream
    ifstream fin;
    ofstream fout;
    
    //Open the text file where period data is stored
    fin.open("periods.txt");
    fout.open("periods.txt");
    
    //Read all periods within text file and store them in the period vector for easy manipulation
    while (fin.good()) {
        fin >> tempPeriod.year >> tempPeriod.month >> tempPeriod.day >> tempPeriod.length;
        allPeriods.push_back(tempPeriod);
    }
    
    //A couple variables that will make operation easier
    avgCycleLength = findAverageCycle(allPeriods);
    int last = allPeriods.size();
    
    cout << "Bloody Times v 1.0" << endl;
    
    //Main menu
    while (desiredAction != 0) {
        cout << "1. Record Period" << endl;
        cout << "2. Display last 5 periods" << endl;
        cout << "3. Display next expected period" << endl;
        cout << "0. Exit" << endl;
        
        cout << "Please choose a menu option by entering the corresponding number: ";
        cin >> desiredAction;
        
        //Exit option
        if (desiredAction == 0) break;
        
        //Uses a function to record a period, pushes it back to the period vector, updates average cycle length
        else if (desiredAction == 1) {
            recordPeriod(tempPeriod);
            fout << tempPeriod.year << " " << tempPeriod.month << " " << tempPeriod.day << " " << tempPeriod.length << endl;
            allPeriods.push_back(tempPeriod);
            avgCycleLength = findAverageCycle(allPeriods);
            last += 1;
        }
        
        //Displays the last 5 recorded periods. If less than 5 periods have been recorded program will display all available ones
        else if (desiredAction == 2) {
            if (allPeriods.size() < 5) {
                for (int i = 0; i < allPeriods.size(); i++) {
                    printPeriod(allPeriods[i]);
                }
            }
            else {
                for (int i = allPeriods.size(); i > (allPeriods.size() - 5); i--) {
                    printPeriod(allPeriods[i]);
                }
            }
        }
        
        //Displays last period and average cycle length
        else if (desiredAction == 3) {
            cout << "Your next period is expected to be " << avgCycleLength << " days from your last period on " << allPeriods[last-1].month << "/" << allPeriods[last-1].day << "/" << allPeriods[last-1].year << endl;
        }
    }
    
    return 0;
}
