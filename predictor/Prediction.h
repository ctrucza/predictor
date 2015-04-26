#ifndef PREDICTION_H
#define PREDICTION_H

template <typename Symbol>
class Prediction {
public:
	Symbol symbol;
	double confidence = 0.0;
	int occurences = 0;

	bool is_null(){
		return (occurences == 0);
	}
};

#endif