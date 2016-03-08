#include <iostream>
#include <ArgParser.hpp>

using namespace std;
using namespace lap;

int main (int argc, char **argv) {
	ArgParser args;
	args.expect ("--help", "gives user the help string", [] {
				cout << "Ajuda eu!" << endl;
				return false;
			});
	args.parse (argc, argv);
	return 0;
}
