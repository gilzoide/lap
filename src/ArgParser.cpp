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
#include <iomanip>
#include <algorithm>

using namespace std;

namespace lap {

ArgParser::ArgParser () {}


ArgParser::~ArgParser () {
	// delete all Opt pointers but the aliases
	for (auto & opt : knownOpts) {
		if (opt.first != opt.second->alias) {
			delete opt.second;
		}
	}
}


//----    BoolOpt    ----//
// Don't stop
void ArgParser::on (const string& option, const string& description,
		boolOptFunc callback) {
	on (option, "", description, callback);
}
void ArgParser::on (const string& option, const string& optionAlias,
		const string& description, boolOptFunc callback) {
	registerOpt (option, optionAlias, description, false, callback);
}


// Stop
void ArgParser::stopOn (const string& option, const string& description,
		boolOptFunc callback) {
	stopOn (option, "", description, callback);
}
void ArgParser::stopOn (const string& option, const string& optionAlias,
		const string& description, boolOptFunc callback) {
	registerOpt (option, optionAlias, description, true, callback);
}


// Register, the common (and abstracted away) thing
void ArgParser::registerOpt (const string& option, const string& optionAlias,
		const string& description, bool stop, boolOptFunc callback) {
	if (!option.empty ()) {
		// create BoolArg and insert it
		auto newArg = new BoolOpt (option, optionAlias, description, stop,
				callback);
		knownOpts.insert (make_pair (option, newArg));

		// there's an alias, insert it too
		if (!optionAlias.empty ()) {
			knownOpts.insert (make_pair (optionAlias, newArg));
		}
	}
	else {
		throw LAP_API_EXCEPTION ("ArgParser::on", "Option name can't be empty!");
	}
}


//----    StrOpt    ----//
// Don't stop
void ArgParser::on (const string& option, const string& description,
		unsigned int n, initializer_list<string> argNames, strOptFunc callback) {
	on (option, "", description, n, argNames, callback);
}
void ArgParser::on (const string& option, const string& optionAlias,
		const string& description, unsigned int n,
		initializer_list<string> argNames, strOptFunc callback) {
	registerOpt (option, optionAlias, description, false, n, argNames, callback);
}


// Stop
void ArgParser::stopOn (const string& option, const string& description,
		unsigned int n, initializer_list<string> argNames, strOptFunc callback) {
	stopOn (option, "", description, n, argNames, callback);
}
void ArgParser::stopOn (const string& option, const string& optionAlias,
		const string& description, unsigned int n,
		initializer_list<string> argNames, strOptFunc callback) {
	registerOpt (option, optionAlias, description, true, n, argNames, callback);
}


// Register, the common (and abstracted away) thing
void ArgParser::registerOpt (const string& option, const string& optionAlias,
		const string& description, bool stop, unsigned int n,
		initializer_list<string> argNames, strOptFunc callback) {
	if (!option.empty ()) {
		// create StrArg and insert it
		auto newArg = new StrOpt (option, optionAlias, description, stop, n,
				argNames, callback);
		knownOpts.insert (make_pair (option, newArg));

		// there's an alias, insert it too
		if (!optionAlias.empty ()) {
			knownOpts.insert (make_pair (optionAlias, newArg));
		}
	}
	else {
		throw LAP_API_EXCEPTION ("ArgParser::on", "Option name can't be empty!");
	}
}



argVector ArgParser::parse (int argc, char **argv) {
	// a vector to store the unknown options
	argVector unknownOpts;
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

// MACRO that throws the "not enough arguments" exception, used so that the
// message is the same either when there are no arguments or any of them is a
// known option
#define COMPLAIN_NOT_ENOUGH_ARGUMENTS(found) \
	ostringstream os; \
	os << "Not enough arguments for \"" << *argv << "\" option : " << \
			advance - 1 << " expected, found " << found; \
	throw Exception (os.str ())

			// maybe there are not enough arguments
			if (advance > (unsigned int) argc) {
				COMPLAIN_NOT_ENOUGH_ARGUMENTS (argc - 1);
			}
			for (i = 1; i < advance; i++) {
				// if any extra argument needed is a known option, complain
				if (knownOpts.find (argv[i]) != knownOpts.end ()) {
					COMPLAIN_NOT_ENOUGH_ARGUMENTS (i - 1);
				}
			}
#undef COMPLAIN_NOT_ENOUGH_ARGUMENTS

			// and go parse stuff. If asked to stop, do it
			opt->match (argc, argv);
			if (opt->stop) {
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
void ArgParser::parseAndRemove (int& argc, char **& argv) {
	auto unknownOpts = parse (argc, argv);
	argc = unknownOpts.size ();
	move (unknownOpts.begin (), unknownOpts.end (), argv);
}


void ArgParser::showHelp (const string& prefix, const string& sufix) {
	cout << prefix << endl;
	if (!knownOpts.empty ()) {
		cout << "OPTIONS:" << endl;
		for (const auto & entry : knownOpts) {
			auto opt = entry.second;
			if (entry.first == opt->name) {
				// option name/alias and args (if any)
				cout << "    " << left << setw (39) << opt->getUsage ();
				// and description
				cout << ' ' << opt->description << endl;
			}
		}
		cout << sufix << endl;
	}
}

}
