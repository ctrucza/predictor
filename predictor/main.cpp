#include <iostream>
#include <string>
#include <map>
#include <algorithm>
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
		auto result = max_element(f.begin(), f.end(), f.value_comp());
		if (result == f.end())
			return Symbol();
		return result->first;
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
	string word;
	while (cin >> word){
		transform(word.begin(), word.end(), word.begin(), tolower);
		predictor.add(word);
	}
	predictor.dump();
}