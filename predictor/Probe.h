#ifndef PROBE_H
#define PROBE_H

template <typename Symbol>
class Probe {
public:
	double measure_performance(Predictor<Symbol>& predictor, Corpus<Symbol>& corpus) {
		Symbol last_word = Symbol();
		int good_predictions = 0;
		int bad_predictions = 0;
		double confidence = 0.0;

		corpus.visit([&](const Symbol& s) {
			Prediction<Symbol> prediction = predictor.predict(last_word);
			Symbol predicted_symbol = prediction.symbol;
			if (predicted_symbol == s) {
				good_predictions++;
				confidence += prediction.confidence;
			} else {
				bad_predictions++;
				confidence -= prediction.confidence;
			}
			last_word = s;
		});

		return (double)good_predictions / (double)(good_predictions + bad_predictions);;
		//return confidence / (double)(good_predictions + bad_predictions);;
	}
};

#endif