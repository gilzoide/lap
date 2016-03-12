lap
===
Lambda Argument Parser, a functional style C++11 library for parsing command
line arguments


BUILDING AND INSTALLING
-----------------------
Build and install with [scons](http://www.scons.org/) or
[hell](https://github.com/gilzoide/hell).
Debug build with flag `debug=1`.


USAGE
-----
1. Include lap header in your source
2. Create a parser object
3. Set the wanted options and their callbacks
4. Call `parse` method
5. Use remaining args, if needed
6. Compile with `-std=c++11` and `-llap` or `$(pkg-config --libs lap)`

```cpp
#include <lap/lap.hpp>
#include <iostream>

int main (int argc, char **argv) {
	lap::ArgParser parser;
	//---- Boolean options (any position, no arguments) ----//
	parser.expect ("-a", "--advice", "gives user some advice", [] {
				std::cout << "Always indent your code!" << std::endl;
				return true;
			});
	// see that it's easy to make a help option
	parser.expect ("-h", "--help", "gives some help in your life", [&parser] {
				parser.showHelp ("Lap README example help", "Use wisely");
				return false;
			});
	// and to make a "end of options" option too
	parser.expect ("--", "stop reading options", [] {
				return false;
			});

	//---- String options (any position, N mandatory arguments) ----//
	parser.expect ("-s", "--size", "set window size", 2, {"width", "height"},
			[] (vector<const char *> v) {
				std::cout << "Window size: " << v[0] << 'x' << v[1] << std::endl;
				return true;
			});

	// parse method returns the unmatched arguments (or throws exception)
	try {
		auto remainingArgs = parser.parse (argc, argv);
		for (auto & arg : remainingArgs) {
			std::cout << "Unmatched arg" << arg << std::endl;
		}
	}
	catch (exception& ex) {
		std::cerr << ex.what () << std::endl;
	}
	
	return 0;
}
```
