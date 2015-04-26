#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <functional>

#include "Frequencies.h"
#include "Predictor.h"
#include "Corpus.h"
#include "Probe.h"

int main() {
	typedef std::string Symbol;

	Corpus<Symbol> corpus;
	corpus.load(std::cin, [](Symbol& s) {
		//s = tolower(s);
		transform(s.begin(), s.end(), s.begin(), tolower);
		return s; 
	});
	
	Predictor<Symbol> predictor;
	corpus.visit([&](const Symbol& symbol) {
		predictor.add(symbol); 
	});
	
	Probe<Symbol> probe;
	double performance = probe.measure_performance(predictor, corpus);
	std::cout << "performance: " << performance << std::endl;

	predictor.dump();


}