/* lap, a functional style C++11 library for parsing command line arguments
 * Copyright (C) <2016> <gilzoide>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Any bugs should be reported to <gilzoide@gmail.com>
 */

#include <ArgParser.hpp>
#include <Exception.hpp>

#include <iostream>

using namespace std;

namespace lap {

ArgParser::ArgParser () {}


ArgParser::~ArgParser () {
	// delete all Opt pointers
	for (auto & opt : knownOpts) {
		if (opt.first != opt.second->alias) {
			delete opt.second;
		}
	}
}


void ArgParser::expect (const string& option, const string& description,
		boolOptFunc callback, const string& optionAlias) {
	if (!option.empty ()) {
		// create BoolArg and insert it
		auto newArg = new BoolOpt (description, callback, optionAlias);
		knownOpts.insert (make_pair (option, newArg));

		// there's an alias, insert it too
		if (!optionAlias.empty ()) {
			knownOpts.insert (make_pair (option, newArg));
		}
	}
	else {
		throw Exception ("ArgParser::expect", "Option name can't be empty!");
	}
}


void ArgParser::expect (const string& option, const string& description, int n,
			strOptFunc callback, const string& optionAlias) {
	if (!option.empty ()) {
		// create StrArg and insert it
		auto newArg = new StrOpt (description, n, callback, optionAlias);
		knownOpts.insert (make_pair (option, newArg));

		// there's an alias, insert it too
		if (!optionAlias.empty ()) {
			knownOpts.insert (make_pair (option, newArg));
		}
	}
	else {
		throw Exception ("ArgParser::expect", "Option name can't be empty!");
	}
}



void ArgParser::parse (int argc, char **argv) {
	// argv iterator
	auto it = argv;
	for (int i = 0; i < argc; i++) {
		cout << *it << endl;
		it++;
	}

	for (auto & arg : knownOpts) {
		cout << arg.first << ": " << arg.second->description << endl;
	}
}

}
