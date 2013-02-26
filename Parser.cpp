#include "Parser.h"

#include <iostream>
#include <sstream>

using namespace std;

string BaseParser::makeUID(int number)
{
    string word;
 
    char unique = 0xFF;
    word += unique;

    stringstream converter;
    converter << number;
    word += converter.str();

    return word;
}

string& BaseParser::getWord(int begin)
{
    for (int i = 0; i < patterns.size(); i++)
    {
        if (begin < patterns[i].size())
            return patterns[i][begin];
        begin -= patterns[i].size() ;
    }
}

int BaseParser::getNumber(int begin)
{
    for (int i = 0; i < patterns.size(); i++)
    {
        if ( begin < patterns[i].size() )
            return i;
        begin -= patterns[i].size();
    }
}

int BoundaryParser::utf8Size(uint8_t byte)
{
    if ( ( byte & 0x80 ) == 0 )
        return 1;
    else if ( ( byte & 0xE0 ) == 0xC0 )
        return 2;
    else if ( ( byte & 0xF0 ) == 0xE0 )
        return 3;
    else if ( ( byte & 0xF8 ) == 0xF0 )
        return 4;
}

void BoundaryParser::readInput()
{
    int number = 0;

    while ( cin.good() )
    {
        readFileCompletely(number);
        number++;
    }
}

void BoundaryParser::readFileCompletely(int number)
{
    vector<string> file = vector<string>();
    string word = "";
    uint8_t c = 0;

    while ( cin.good() )
    {
        c = cin.get();
        if ( cin.good() )
        {
            //delimiter
            if ( c == '\n' )
                break;

            int size = utf8Size(c);
            word += c;

            for (int i = 1; i < size; ++i)
            {
                c = cin.get();
                word += c;
            }

            if ( !word.empty() )
            {
                file.push_back(word);
                totalLength++;
                word.clear();
            }
        }
    }

    patterns.push_back(file);
}