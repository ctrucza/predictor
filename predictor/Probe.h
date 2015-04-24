#ifndef PROBE_H
#define PROBE_H

template <typename Symbol>
class Probe {
public:
	double measure_performance(Predictor<Symbol>& predictor, Corpus<Symbol>& corpus) {
		Symbol last_word;
		int good_predictions = 0;
		int bad_predictions = 0;

		corpus.visit([&](const Symbol& s) {
			Symbol prediction = predictor.predict(last_word);
			if (prediction == s) {
				good_predictions++;
			} else {
				bad_predictions++;
			}
			last_word = s;
		});

		return (double)good_predictions / (double)(good_predictions + bad_predictions);;
	}
};

#endif