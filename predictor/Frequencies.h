#ifndef FREQUENCIES_H
#define FREQUENCIES_H

#include <map>
#include <ostream>
#include "Prediction.h"

template <typename Symbol>
class Frequencies {
private:
	int total = 0;
	std::map<Symbol, int> occurences;

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const Frequencies<T>& f);

	std::ostream& print(std::ostream& os) const {
		for (std::map<Symbol, int>::const_iterator i = occurences.begin(); i != occurences.end(); ++i) {
			os << "[" << i->first << "](" << i->second << ") ";
		}
		return os;
	}

public:
	void add(const Symbol& symbol) {
		occurences[symbol]++;
		total++;
	}

	int size() const {
		return occurences.size();
	}

	Prediction<Symbol> find_best() const {
		Symbol best_symbol;
		double best_score = 0.0;
		for (auto i = occurences.begin(); i != occurences.end(); ++i) {
			double score = (double)i->second/(double)total;
			if (i->second > best_score) {
				best_score = i->second;
				best_symbol = i->first;
			}
		}

		Prediction<Symbol> result;
		result.symbol = best_symbol;
		result.confidence = (double)best_score/(double)total;

		return result;
	}
};

template <typename Symbol>
std::ostream& operator<<(std::ostream& os, const Frequencies<Symbol>& f) {
	return f.print(os);
}

#endif