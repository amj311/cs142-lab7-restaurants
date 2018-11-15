/*
    @@@@@@   @@@@@@@@ @@   @@@  @@   @@@ @@@@@@@@ @@@@@@
   @@   @@     @@    @@@   @@  @@@   @@ @@       @@   @@
  @@    @@    @@    @@ @  @@  @@ @  @@ @@@@@@   @@@@@@
 @@   @@     @@    @@  @ @@  @@  @ @@ @@       @@   @@
@@@@@@   @@@@@@@@ @@   @@@  @@   @@@ @@@@@@@@ @@    @@

            @@@@@@   @@@@@@@@ @@@@@@@@ @@@@@@@@ @@@      @@@@@@@@
           @@   @@  @@    @@    @@       @@    @@@      @@
          @@@@@@   @@@@@@@@    @@       @@    @@@      @@@@@@
         @@    @@ @@    @@    @@       @@    @@@      @@
        @@@@@@@  @@    @@    @@       @@    @@@@@@@@ @@@@@@@@

Created by Arthur Judd, amjudd315@gmail.com, online section
Created using VS

Test Case 1:
listRestaurants = {"a","b","c","d"}.
Testing: CutList() for cutIdx = 2;
Expected result: listRestaurants = ("c","d","a","b")
Results: passed.

Test Case 2:
listRestaurants = {"a","b","c","d","e","f","g"}.
Testing: ShuffleList().
Expected result: "The current tournament size (7) is not a power of two (2, 4, 8...).
                  A shuffle is not possible. Please add or remove restaurants."
Result: passed.

Test Case 3:
listRestaurants = {"a","b","c","d","e","f","g","h"}.
Testing: ShuffleList().
Expected result: listRestaurants = ("e","a",f","b","g","c","h","d").
Result: passed.

Test Case 4:
listRestaurants = {"a","b","c","d"}.
Testing: RunBattle() for userChoice 1, 1, 1.
Expected result:
    Round 1 - winner: a, loser: b;
    Round 2 - winner: c, loser: d;
    Round 3 - winner: a, loser: c;
    Winner: a.
Result: passed.
*/


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

void PrintMenu() {
	cout << "Please select one of the following options:" << endl << endl
		<< "quit - Quit the program" << endl
		<< "display - Display all restaurants" << endl
		<< "add - Add a restaurant" << endl
		<< "remove - Remove a restaurant" << endl
		<< "cut - \"Cut\" the list of restaurants" << endl
		<< "shuffle - \"Shuffle\" the list of restaurants" << endl
		<< "battle - Begin the tournament" << endl
		<< "options - Print the options menu" << endl << endl;
}

// valid getline for strings
void ValidGetLine(string& targetStr, const string promptStr, const string failStr) {
	cout << promptStr << endl;
	getline(cin, targetStr);
	if (targetStr == "" || targetStr == " ") {
		getline(cin, targetStr);
	}

	while (cin.fail()) {
		// Clear error state
		cin.clear();

		// Ignore characters in stream until newline
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << failStr << endl << endl;
		cout << promptStr;
		cin >> targetStr;
	}

	return;
}


//Input cin for strings
void ValidCin(string& targetStr, const string promptStr, const string failStr) {
	cout << promptStr;
	cin >> targetStr;
	cout << endl;

	while (cin.fail()) {
		// Clear error state
		cin.clear();

		// Ignore characters in stream until newline
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << failStr << endl << endl;
		cout << promptStr;
		cin >> targetStr;
	}

	return;
}

//Input cin for integers
void ValidCin(int& targetInt, const string promptStr, const string failStr, const int minInt = 0, const int maxInt = 0) {
	cout << promptStr;
	cin >> targetInt;
	cout << endl;

	while (cin.fail() || targetInt < minInt || (maxInt != 0 && targetInt > maxInt)) {
		// Clear error state
		cin.clear();

		// Ignore characters in stream until newline
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << failStr << endl << endl;
		cout << promptStr;
		cin >> targetInt;
	}

	return;
}

void DisplayList(vector<string>& listRestaurants, int& numRestaurants) {

	cout << "Here are the current restaurants:" << endl << endl;

	for (int curName = 0; curName < numRestaurants; curName++) {
		cout << "\t\"" << listRestaurants.at(curName) << "\"" << endl;
	}

	cout << endl << endl;
}

int FindInList(string& nameToFind, vector<string>& listRestaurants, int& numRestaurants){
    for (int curName = 0; curName < numRestaurants; curName++) {
        if (listRestaurants.at(curName) == nameToFind) {
            return curName;
        }
    }
    return -1;
}

void AddRestaurant(vector<string>& listRestaurants, int& numRestaurants) {
	string newName;
	ValidGetLine(newName, "What is the name of the restaurant you want to add?", "Invalid selection.");

	if (FindInList(newName, listRestaurants, numRestaurants) < 0) {
		numRestaurants++;
		listRestaurants.push_back(newName);
		cout << newName << " has been added." << endl << endl;
	}
	else {
        cout << "That restaurant is already on the list, you can not add it again." << endl << endl;
	}
}

void RemoveRestaurant(vector<string>& listRestaurants, int& numRestaurants) {
	string nameToRemove;
	ValidGetLine(nameToRemove, "What is the name of the restaurant you want to remove?", "Invalid selection.");
	int findIdx = FindInList(nameToRemove, listRestaurants, numRestaurants);

	if (findIdx >= 0) {
			numRestaurants--;
			listRestaurants.erase(listRestaurants.begin() + findIdx);
			cout << nameToRemove << " has been removed." << endl << endl;
	}
	else {
        cout << "That restaurant is not on the list, you can not remove it." << endl << endl;
	}
}

void CutList(vector<string>& listRestaurants, int& numRestaurants){
    int cutIdx = 0;
    ValidCin(cutIdx,
             "How many restaurants should be taken from the top and put on the bottom?",
             "The cut number must be between 0 and " + to_string(numRestaurants),
             0,
             numRestaurants);


    vector<string> newList(numRestaurants);
    int copyIdx = cutIdx;

    for (int i = 0; i < numRestaurants; i++) {
		if (copyIdx > numRestaurants-1) {
			copyIdx = 0;
		}
		newList.at(i) = (listRestaurants.at(copyIdx));
		copyIdx++;
	}

    listRestaurants = newList;
    return;
}

bool PowerOfTwo(int numberToCheck){
    for(int pwrTwo = 2; pwrTwo <= numberToCheck; pwrTwo *= 2){
        if(pwrTwo == numberToCheck){
            return true;
        }
    }

    return false;
}

void ShuffleList(vector<string>& listRestaurants, int& numRestaurants){
    const int HALF_DECK = numRestaurants/2;
    vector<string> halfList(HALF_DECK);
    vector<string> newList (0);

    if (PowerOfTwo(numRestaurants)){
        for (int i = 0; i < HALF_DECK; i++) {
            halfList.at(i) = listRestaurants.at(HALF_DECK + i);
        }

        for(int i = 0; i < HALF_DECK; i++){
            newList.push_back(halfList.at(i));
            newList.push_back(listRestaurants.at(i));
        }

        listRestaurants = newList;
    }
    else {
        cout << "The current tournament size (" << to_string(numRestaurants) << ") is not a power of two (2, 4, 8...)." << endl
            << "A shuffle is not possible. Please add or remove restaurants." << endl;
    }

    return;
}

void RunBattle(vector<string>& listRestaurants, int& numRestaurants){
    if (PowerOfTwo(numRestaurants)){
        vector<string> battleBracket(numRestaurants);
        battleBracket = listRestaurants;

        for(int curRound = 1; battleBracket.size()>1; curRound++){
            cout << "Round: " << curRound << endl << endl;
            int numMatches = battleBracket.size()/2;

            for(int curMatch = 0; curMatch < numMatches; curMatch++){
                string option1 = battleBracket.at(curMatch);
                string option2 = battleBracket.at(curMatch+1);
                int userChoice;
                ValidCin(userChoice,
                         "Type \"1\" if you prefer " + option1 + " or"
                            + "\ntype \"2\" if you prefer " + option2
                            + "\nChoice: \n",
                         "Invalid choice",
                         1, 2);

                if(userChoice == 1){
                    battleBracket.erase(battleBracket.begin() + curMatch+1);
                }
                else if(userChoice == 2){
                    battleBracket.erase(battleBracket.begin() + curMatch);
                }
            }
        }
        cout << "The winning restaurant is " << battleBracket.at(0) << "." << endl << endl;

    }
    else {
        cout << "The current tournament size (" << to_string(numRestaurants) << ") is not a power of two (2, 4, 8...)." << endl
            << "A battle is not possible. Please add or remove restaurants." << endl;
    }

    return;
}

int main() {
	int numRestaurants = 0;
	vector<string> listRestaurants(numRestaurants);
	string userTask = "unset";

	//Game Start
	cout << "Welcome to the restaurant battle!  Enter \"options\" to see options." << endl << endl;
	ValidCin(userTask, "Enter your selection: ", "Invalid selection.");

	//Game Loop
	while (userTask != "quit") {

		//Present Main menu
		if (userTask == "options") {
			PrintMenu();
		}
		else if (userTask == "display") {
			DisplayList(listRestaurants, numRestaurants);
		}
		else if (userTask == "add") {
			AddRestaurant(listRestaurants, numRestaurants);
		}
		else if (userTask == "remove") {
			RemoveRestaurant(listRestaurants, numRestaurants);
		}
		else if (userTask == "cut") {
            CutList(listRestaurants, numRestaurants);
		}
		else if (userTask == "shuffle") {
            ShuffleList(listRestaurants, numRestaurants);
		}
		else if (userTask == "battle") {
            RunBattle(listRestaurants, numRestaurants);
		}

		// invalid input
		else {
			cout << "Invalid selection" << endl;
			PrintMenu();
		}

		ValidCin(userTask, "Enter your selection: ", "Invalid selection.");

	}
	cout << "Goodbye!";

	//system("pause");
	return 0;
}
