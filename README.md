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
	// boolean option (any position, no arguments
	parser.expect ("-h", "--help", "gives some help in your life", [] {
				std::cout << "Always indent your code!" << std::endl;
				return false;
			});

	// parse method returns the unmatched arguments
	auto remainingArgs = parser.parse (argc, argv);
	for (auto & arg : remainingArgs) {
		std::cout << arg << std::endl;
	}
	
	return 0;
}
```
