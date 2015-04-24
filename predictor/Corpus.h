#ifndef CORPUS_H
#define CORPUS_H

#include <list>
#include <istream>
#include <functional>

template <typename Symbol>
class Corpus {
private:
	std::list<Symbol> corpus;
public:
	void load(std::istream& is, std::function<Symbol(Symbol&)> preprocessor) {
		Symbol word;
		while (is >> word) {
			word = preprocessor(word);
			corpus.push_back(word);
		}
	}

	void visit(std::function<void(const Symbol&)> visitor) {
		for (auto i = corpus.begin(); i != corpus.end(); ++i) {
			visitor(*i);
		}
	}
};

#endif