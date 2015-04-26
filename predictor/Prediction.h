#ifndef PREDICTION_H
#define PREDICTION_H

template <typename Symbol>
class Prediction {
public:
	Symbol symbol;
	double confidence;
	int occurences;
};

#endif