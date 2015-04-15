#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <list>

using namespace std;

template <typename Symbol>
class Frequencies {
private:
	int total = 0;
	map<Symbol, int> occurences;

	template <typename T>
	friend ostream& operator<<(ostream& os, const Frequencies<T>& f);

	ostream& print(ostream& os) const {
		for (map<Symbol, int>::const_iterator i = occurences.begin(); i != occurences.end(); ++i) {
			os << "[" << i->first << "](" << i->second << ") ";
		}
		return os;
	}

public:
	void add(const Symbol& other) {
		occurences[other]++;
		total++;
	}

	int size() const {
		return occurences.size();
	}

	Symbol find_best() const {
		Symbol result;
		double best_score = 0.0;
		for (auto i = occurences.begin(); i != occurences.end(); ++i) {
			double score = (double)i->second/(double)total;
			if (i->second > best_score) {
				best_score = i->second;
				result = i->first;
			}
		}
		return result;
	}
};

template <typename Symbol>
ostream& operator<<(ostream& os, const Frequencies<Symbol>& f) {
	return f.print(os);
}

template <typename Symbol>
class Predictor {
private:
	typedef map<Symbol, Frequencies<Symbol>> Neighbours;
	Neighbours successors;
	Neighbours predecessors;

	Symbol last_symbol;

	Symbol best_of(const Frequencies<Symbol>& f) const {
		return f.find_best();
	}

	void print_neighbours(ostream& os, const Neighbours n) {
		for (Neighbours::const_iterator i = n.begin(); i != n.end(); ++i) {
			cout << "[" << i->first << "](" << i->second.size() << ") ";
			cout << i->second;
			cout << "" << endl;
		}
	}
public:
	void add(const Symbol& s) {
		successors[last_symbol].add(s);
		predecessors[s].add(last_symbol);
		last_symbol = s;
	}

	Symbol predict(const Symbol& previous) {
		return best_of(successors[previous]);
	}

	void dump() {
		print_neighbours(cout, successors);
		print_neighbours(cout, predecessors);
	}
};

int main() {
	Predictor<string> predictor;

	list<string> corpus;
	string word;
	while (cin >> word) {
		transform(word.begin(), word.end(), word.begin(), tolower);
		corpus.push_back(word);
	}

	for (auto i = corpus.begin(); i != corpus.end(); ++i) {
		predictor.add(*i);
	}

	string last_word;
	int good_predictions = 0;
	int bad_predictions = 0;
	for (auto i = corpus.begin(); i != corpus.end(); ++i) {
		string prediction = predictor.predict(last_word);
		if (prediction == *i) {
			good_predictions++;
		} else {
			bad_predictions++;
		}
		last_word = *i;
	}
	double performance = (double)good_predictions / (double)(good_predictions + bad_predictions);
	cout << "performance: " << performance << endl;
	predictor.dump();
}