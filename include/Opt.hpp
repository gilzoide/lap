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

/** @file Opt.hpp
 * Entry of an expected option. Options are non-positional arguments
 */
#pragma once

#include <string>

using namespace std;

namespace lap {

/**
 * Options, that may be in any place on argv (non-positional arguments)
 *
 * @note Options may have an alias (like "-h" and "--help")
 */
class Opt {
public:
	/**
	 * Ctor
	 *
	 * @param name Option name
	 * @param alias Option alias
	 * @param description Option description
	 */
	Opt (const string& name, const string& alias, const string& description);
	/**
	 * Ctor overload without alias
	 */
	Opt (const string& name, const string& description);

	/**
	 * Virtual dtor
	 */
	virtual ~Opt ();

	/**
	 * Function called when there was a match
	 *
	 * @param argc Number of available arguments
	 * @param argv Available arguments
	 *
	 * @return `true` if ArgParser should continue to parse arguments
	 * @return `false` otherwise
	 *
	 * @throws Exception if something went wrong (like error on extra arguments)
	 */
	virtual bool match (int argc, char **argv) = 0;

	/**
	 * Returns how many extra arguments Arg will consume
	 *
	 * This is used to know how many more arguments will be consumed, so that
	 * ArgParser can skip them, and check if none of them are registered options
	 *
	 * @return Number of extra arguments consumed (if none, return 0)
	 */
	virtual unsigned int numExtraArguments () = 0;

	/**
	 * Returns a simple usage string, for documentation (like help info)
	 *
	 * @return Option usage string with name|alias
	 */
	virtual string getUsage ();

	/// Option name
	string name;

	/// Option description, used for help/usage
	string description;

	/// Option alias
	string alias;
};

}

