#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <functional>

#include "Frequencies.h"
#include "Predictor.h"
#include "Corpus.h"
#include "Probe.h"

using namespace std;

int main() {
	Corpus<string> corpus;
	corpus.load(cin, [](string& s) {
		transform(s.begin(), s.end(), s.begin(), tolower);
		return s; 
	});
	
	Predictor<string> predictor;
	corpus.visit([&](const string& symbol) {
		predictor.add(symbol); 
	});
	
	Probe<string> probe;
	double performance = probe.measure_performance(predictor, corpus);
	cout << "performance: " << performance << endl;

	predictor.dump();


}