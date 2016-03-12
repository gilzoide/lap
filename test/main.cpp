#include <lap.hpp>
#include <iostream>

using namespace std;

int main (int argc, char **argv) {
	lap::ArgParser parser;
	//---- Boolean options (any position, no arguments) ----//
	parser.registerOpt ("-a", "--advice", "gives user some advice", [] {
				cout << "Always indent your code!" << endl;
				return true;
			});
	// see that it's easy to make a help option
	parser.registerOpt ("-h", "--help", "gives some help in your life", [&parser] {
				parser.showHelp ("Lap README example help", "Use wisely");
				return false;
			});
	// and to make a "end of options" option too
	parser.registerOpt ("--", "stop reading options", [] {
				return false;
			});

	//---- String options (any position, N mandatory arguments) ----//
	parser.registerOpt ("-s", "--size", "set window size", 2, {"width", "height"},
			[] (vector<const char *> v) {
				try {
					cout << "Window size: " << stoi (v[0]) << 'x' << stoi (v[1]) << endl;
				}
				catch (exception& ex) {
					throw;
				}
				return true;
			});

	// parse method returns the unmatched arguments (or throws exception)
	try {
		auto remainingArgs = parser.parse (argc, argv);
		for (auto & arg : remainingArgs) {
			cout << "Unmatched arg: \"" << arg << '"' << endl;
		}
	}
	catch (exception& ex) {
		cerr << "ArgParse error: " << ex.what () << endl;
	}
	
	return 0;
}
