#pragma once

#include <vector>
#include <stdint.h>
#include <string>

using namespace std;

class BaseParser
{
protected:
    vector< vector<string> > patterns;
    
public:
	int totalFiles;
	int totalLength;

    BaseParser():
    		patterns(vector < vector < string > > () )
		,   totalFiles(0)
    	, 	totalLength(0)
    {}

    string& getWord(int number);
    int getNumber(int number);
    
    virtual ~BaseParser() {}
};

class BoundaryParser : public BaseParser
{
private:
    int utf8Size(uint8_t byte);

public:
    void readInput();
    void readFileCompletely(int number);

    ~BoundaryParser() {}
};
