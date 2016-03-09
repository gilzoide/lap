#include <iostream>
#include <lap.hpp>

using namespace std;
using namespace lap;

int main (int argc, char **argv) {
	ArgParser args;
	args.expect ("-h", "--help", "gives user the help string", [] {
				cout << "Ajuda eu!" << endl;
				return false;
			});
	args.expect ("-a", "--answer", "give us the answer", 1, [] (vector<const char *> v) {
				if (v[0] != string ("42")) {
					cout << "resposta errada!" << endl;
				}
				else {
					cout << "resposta certa xD" << endl;
				}
				return true;
			});
	auto unknown = args.parse (argc, argv);
	for (auto & arg : unknown) {
		cout << "Unknown arg: " << arg << endl;
	}
	return 0;
}
