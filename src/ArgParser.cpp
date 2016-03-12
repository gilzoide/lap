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

#include "ArgParser.hpp"
#include "debug.hpp"

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


void ArgParser::expect (const string& option, const string& optionAlias,
		const string& description, boolOptFunc callback) {
	if (!option.empty ()) {
		// create BoolArg and insert it
		auto newArg = new BoolOpt (option, optionAlias, description, callback);
		knownOpts.insert (make_pair (option, newArg));

		// there's an alias, insert it too
		if (!optionAlias.empty ()) {
			knownOpts.insert (make_pair (optionAlias, newArg));
		}
	}
	else {
		throw LAP_API_EXCEPTION ("ArgParser::expect", "Option name can't be empty!");
	}
}
void ArgParser::expect (const string& option, const string& description,
			boolOptFunc callback) {
	expect (option, "", description, callback);
}


void ArgParser::expect (const string& option, const string& optionAlias,
			const string& description, unsigned int n,
			initializer_list<string> argNames, strOptFunc callback) {
	if (!option.empty ()) {
		// create StrArg and insert it
		auto newArg = new StrOpt (option, optionAlias, description, n,
				argNames, callback);
		knownOpts.insert (make_pair (option, newArg));

		// there's an alias, insert it too
		if (!optionAlias.empty ()) {
			knownOpts.insert (make_pair (optionAlias, newArg));
		}
	}
	else {
		throw LAP_API_EXCEPTION ("ArgParser::expect", "Option name can't be empty!");
	}
}
void ArgParser::expect (const string& option, const string& description,
		unsigned int n, strOptFunc callback) {
	expect (option, "", description, n, {}, callback);
}



vector<const char *> ArgParser::parse (int argc, char **argv) {
	// a vector to store the unknown options
	vector<const char *> unknownOpts;
	// how many args will we advance each time
	unsigned int advance;
	unsigned int i;
	
	// while there are arguments left
	while (argc > 0) {
		auto entry = knownOpts.find (*argv);
		// it's a known option
		if (entry != knownOpts.end ()) {
			auto opt = entry->second;
			// get how much we should advance
			advance = opt->numExtraArguments () + 1;

			// maybe there are not enough arguments
			if (advance > argc) {
				throw Exception ("Not enough arguments for \"" +
						string (*argv) + "\" option");
			}
			for (i = 1; i < advance; i++) {
				// if any extra argument needed is a known option, complain
				if (knownOpts.find (argv[i]) != knownOpts.end ()) {
					throw Exception ("Not enough arguments for \"" +
							string (*argv) + "\" option");
				}
			}
			// and go parse stuff. If asked to stop, do it
			if (!opt->match (argc, argv)) {
				// insert rest of arguments on unknownOpts (ignoring current arg)
				unknownOpts.insert (unknownOpts.end (), argv + 1, argv + argc);
				break;
			}
		}
		else {
			unknownOpts.push_back (*argv);
			advance = 1;
		}

		// neeeeeext
		argc -= advance;
		argv += advance;
	}

	return move (unknownOpts);
}


void ArgParser::showHelp (const string& prefix, const string& sufix) {
	cout << prefix << endl;
	if (!knownOpts.empty ()) {
		cout << "OPTIONS:" << endl;
		for (const auto & entry : knownOpts) {
			auto opt = entry.second;
			if (entry.first == opt->name) {
				// option name/alias and args (if any)
				cout << "    " << opt->getUsage ();
				// and description
				cout << " : " << opt->description << endl;
			}
		}
		cout << sufix << endl;
	}
}

}
