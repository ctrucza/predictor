#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <list>

using namespace std;

template <typename Symbol>
class Predictor
{
private:
	typedef map<Symbol, int> Frequencies;
	typedef map<Symbol, Frequencies> Neighbours;
	Neighbours successors;
	Neighbours predecessors;

	Symbol last_symbol;

	Symbol best_of(const Frequencies& f) const {
		Symbol result;
		int best_count = 0;
		for (auto i = f.begin(); i != f.end(); ++i){
			if (i->second > best_count){
				best_count = i->second;
				result = i->first;
			}
		}
		return result;
	}

	void print_occurences(ostream &os, const Frequencies o){
		for (Frequencies::const_iterator i = o.begin(); i != o.end(); ++i){
			cout << "[" << i->first << "](" << i->second << ") ";
		}
	}

	void print_neighbours(ostream& os, const Neighbours n){
		for (Neighbours::const_iterator i = n.begin(); i != n.end(); ++i){
			cout << "[" << i->first << "]("<< i->second.size() <<") ";
			print_occurences(cout, i->second);
			cout << "" << endl;
		}
	}
public:
	void add(const Symbol& s){
		successors[last_symbol][s]++;
		predecessors[s][last_symbol]++;
		last_symbol = s;
	}

	Symbol predict(const Symbol& previous){
		return best_of(successors[previous]);
	}

	void dump(){
		print_neighbours(cout, successors);
		print_neighbours(cout, predecessors);
	}
};

int main(){
	Predictor<string> predictor;

	list<string> corpus;
	string word;
	while (cin >> word){
		transform(word.begin(), word.end(), word.begin(), tolower);
		corpus.push_back(word);
	}

	for (auto i = corpus.begin(); i != corpus.end(); ++i)
	{
		predictor.add(*i);
	}
	
	string last_word;
	int good_predictions = 0;
	int bad_predictions = 0;
	for (auto i = corpus.begin(); i != corpus.end(); ++i)
	{
		string prediction = predictor.predict(last_word);
		if (prediction == *i){
			good_predictions++;
		} else {
			bad_predictions++;
		}
		last_word = *i;
	}
	double performance = (double)good_predictions / (double)(good_predictions + bad_predictions);
	cout << "performance: " << performance << endl;
	//predictor.dump();
}