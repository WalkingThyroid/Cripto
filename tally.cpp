#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(int argc , char* argv[])
{
	char *voter, *vote[10], candidate[10], *signature;

	std::ifstream input( argv[1] );
	for( std::string line; getline( input, line ); )
	{
		sscanf(line, "%s: %s % %s % %s % %s % %s % %s % %s % %s % %s % %s % %",
					voter, candidate[0], vote[0], candidate[1], vote[1], candidate[2], vote[2],
					candidate[3], vote[3], candidate[4], vote[4], candidate[5], vote[5],
					candidate[6], vote[6], candidate[7], vote[7], candidate[8], vote[8],
					candidate[9], vote[9], signature);
	}


}
