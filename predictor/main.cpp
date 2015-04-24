#include <iostream>
#include <string>
#include <algorithm>
#include <list>

#include "Frequencies.h"
#include "Predictor.h"

using namespace std;

list<string> load_corpus() {
	list<string> corpus;
	string word;
	while (cin >> word) {
		transform(word.begin(), word.end(), word.begin(), tolower);
		corpus.push_back(word);
	}
	return corpus;
}

template <typename T>
void measure_performance(Predictor<T>& predictor, const list<string>& corpus) {
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
}

int main() {
	Predictor<string> predictor;

	auto corpus = load_corpus();

	for (auto i = corpus.begin(); i != corpus.end(); ++i) {
		predictor.add(*i);
	}

	measure_performance(predictor, corpus);

	predictor.dump();
}