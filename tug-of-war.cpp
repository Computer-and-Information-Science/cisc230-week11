// The Tug-Of-War problem

#include <cmath>
#include <iostream>
#include <list>
#include <string>
using namespace std;

// Represents a tug-of-war team, with ability to add a member to the team (by
// the person's weight), and methods to determine the size (number of members)
// and weight of the team, retrieve a list of weights of team members, and
// print information about the team.
class Team : private list<int> {
private:
	int sum_weights;
public:
	Team () { sum_weights = 0; }
	void add (int w) { sum_weights += w; push_back(w); }
	int size () const { return list<int>::size(); }
	int weight () const { return sum_weights; }
	list<int> weights () const { return *this; }
	void print (const string& label) const;
};

// A class for finding a solution to the tug-of-war problem. The constructor
// receives a list of weights and is responsible for finding a solution.
// Methods are included to retrieve the difference in size (number of team
// members) and weight of the two teams, and to print information about the
// teams.
class TugOfWar {
private:
	Team team1, team2;
public:
	TugOfWar (list<int> weights);
	int diff_size () const { return abs(team1.size() - team2.size()); }
	int diff_weight () const { return abs(team1.weight() - team2.weight()); }
	void print () const;
};

void print_list (const string& label, const list<int> weights);

int main () {
	// Four test cases, each a list of weights that are to be divided among
	// two teams.
	list<int> test_case_1 = { 145, 225, 130, 125, 170, 140, 180, 120, 175 };
	list<int> test_case_2 = { 150, 203, 170, 125, 105, 195, 160, 187, 174 };
	list<int> test_case_3 = { 200, 150, 175, 202, 110, 132, 180 };
	list<int> test_case_4 = { 135, 170, 155, 165, 190, 210, 140, 115, 165, 160, 229, 190 };

	// Test case #1
	print_list("Test case 1: ", test_case_1);
	TugOfWar(test_case_1).print();
	cout << endl;

	// Test case #2
	print_list("Test case 2: ", test_case_2);
	TugOfWar(test_case_2).print();
	cout << endl;

	// Test case #3
	print_list("Test case 3: ", test_case_3);
	TugOfWar(test_case_3).print();
	cout << endl;

	// Test case #4
	print_list("Test case 4: ", test_case_4);
	TugOfWar(test_case_4).print();

	return 0;
}

// Print information about a team
void Team::print (const string& label) const {
	cout << label;
	for (auto weight: weights())
		cout << ' ' << weight;
	cout << " : Size " << size() << ", Total " << weight() << endl;
}

// Constructor, given a list of weights, assigns the weights to two teams as
// a solution to the problem.
TugOfWar::TugOfWar (list<int> weights) {
	// No real algorithm here other than to alternate players to team as they
	// appear in the given list.
	bool t1 = true;
	for (auto w: weights) {
		(t1 ? team1 : team2).add(w);
		t1 = !t1;
	}
}

// Prints a solution to the tug-of-war problem.
void TugOfWar::print () const {
	team1.print("Team 1: ");
	team2.print("Team 2: ");
	cout << "Size diff: " << diff_size() << ", Weight diff: " <<
		diff_weight() << endl;
}

// Prints a list of weights
void print_list (const string& label, const list<int> weights) {
	cout << label;
	for (auto w: weights)
		cout << ' ' << w;
	cout << endl;
}
