#include <lap.hpp>
#include <iostream>

using namespace std;
using namespace lap;

int main (int argc, char **argv) {
	ArgParser parser;
	//---- Boolean options (any position, no arguments) ----//
	parser.on ("-a", "--advice", "gives user some advice", [] {
				cout << "Always indent your code!" << endl;
			});
	// see that it's easy to make a help option
	parser.stopOn ("-h", "--help", "gives some help in your life", [&parser] {
				parser.showHelp ("Lap README example help", "Use wisely");
			});
	// and to make a "end of options" option too
	parser.stopOn ("--", "stop reading options", [] {});

	//---- String options (any position, N mandatory arguments) ----//
	parser.on ("-s", "--size", "set window size", 2, {"width", "height"},
			[] (argVector v) {
				try {
					cout << "Window size: " << stoi (v[0]) << 'x' << stoi (v[1]) << endl;
				}
				catch (exception& ex) {
					throw;
				}
			});

	// parse method returns the unmatched arguments (or throws exception)
	try {
		// try value method
		auto remainingArgs = parser.parse (argc, argv);
		for (auto & arg : remainingArgs) {
			cout << "Unmatched arg: \"" << arg << '"' << endl;
		}

		cout << endl;
		// try reference method
		parser.parseAndRemove (argc, argv);
		for (int i = 0; i < argc; i++) {
			cout << "Unmatched arg: \"" << argv[i] << '"' << endl;
		}
	}
	catch (exception& ex) {
		cerr << "ArgParse error: " << ex.what () << endl;
	}
	
	return 0;
}
