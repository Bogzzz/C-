#include <string>
using namespace std;

class TRies{

public:
	TRies(string data[],int sz);
	void addWord(const string& newWord);
	bool lookup(const string& word) const;
	int suggest(const string& partialWord, string suggestions[]) const;
	~TRies();	
};