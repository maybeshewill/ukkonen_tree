#include <cstdlib>
#include <iostream>
#include <vector>

#include "Parser.h"
#include "Ukkonen.h"

using namespace std;

int main(int argc, char* argv[])
{
    BaseParser* parser = NULL;

	parser = new BoundaryParser();
	static_cast<BoundaryParser*>(parser)->readInput();

	BaseUkkonen ukk(parser);
	ukk.init();
	
	delete parser;

    return 0;
}