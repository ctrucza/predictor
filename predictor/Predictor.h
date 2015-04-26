#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <map>
#include <ostream>
#include "Prediction.h"

template <typename Symbol>
class Predictor {
private:
	typedef std::map<Symbol, Frequencies<Symbol>> Neighbours;
	Neighbours successors;
	Neighbours predecessors;

	Symbol last_symbol = Symbol();

	Prediction<Symbol> best_of(const Frequencies<Symbol>& f) const {
		return f.find_best();
	}

	void print_neighbours(std::ostream& os, const Neighbours& n) {
		for (Neighbours::const_iterator i = n.begin(); i != n.end(); ++i) {
			os << "[" << i->first << "](" << i->second.size() << ") ";
			os << i->second;
			os << "" << std::endl;
		}
	}

	void prune(Neighbours& n){
		Neighbours result;
		for (auto i = n.begin(); i != n.end(); ++i){
			auto s = i->second;
			if (s.size() == 1){
				auto p = s.find_best();
				if (p.occurences == 1){
					std::cerr << "eliminating " << i->first << " " << i->second << std::endl;
					continue;
				}
			}
			result[i->first] = i->second;
		}
		n = result;
	}
public:
	void add(const Symbol& s) {
		successors[last_symbol].add(s);
		predecessors[s].add(last_symbol);
		last_symbol = s;
	}

	Prediction<Symbol> predict(const Symbol& previous) {
		if (successors.find(previous) == successors.end()){
			return Prediction<Symbol>();
		}
		return best_of(successors[previous]);
	}

	void prune()
	{
		prune(successors);
		prune(predecessors);
	}

	void dump() {
		std::cout << "successors" << std::endl;
		print_neighbours(std::cout, successors);
		std::cout << "predecessors" << std::endl;
		print_neighbours(std::cout, predecessors);
	}
};

#endif