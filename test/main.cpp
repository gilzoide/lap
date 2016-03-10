#include <iostream>
#include <lap.hpp>

using namespace std;
using namespace lap;

int main (int argc, char **argv) {
	ArgParser args;
	args.expect ("-h", "--help", "gives user the help string", [&args] {
				args.showHelp ("Lap test (uh lah lah!)",
						"Any bugs should be reported to <gilzoide@gmail.com>");
				return false;
			});
	args.expect ("-a", "--answer", "give us the ANSWER, mortal!", 1, {"ANSWER"}, [] (vector<const char *> v) {
				if (v[0] != string ("42")) {
					cout << "resposta errada!" << endl;
				}
				else {
					cout << "resposta certa xD" << endl;
				}
				return true;
			});
	args.expect ("--advice", "give user some advice", [] {
				cout << "Always indent your code!" << endl;
				return true;
			});

	try {
		auto unknown = args.parse (argc, argv);
		for (auto & arg : unknown) {
			cout << "Unmatched arg: " << arg << endl;
		}
	}
	catch (exception& ex) {
		cerr << ex.what () << endl;
	}

	return 0;
}
