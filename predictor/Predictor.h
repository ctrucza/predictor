#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <map>
#include <ostream>

template <typename Symbol>
class Predictor {
private:
	typedef std::map<Symbol, Frequencies<Symbol>> Neighbours;
	Neighbours successors;
	Neighbours predecessors;

	Symbol last_symbol;

	Symbol best_of(const Frequencies<Symbol>& f) const {
		return f.find_best();
	}

	void print_neighbours(std::ostream& os, const Neighbours n) {
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

#endif