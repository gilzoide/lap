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

/** @file Arg.hpp
 * Entry of an expected argument. There are several types of Args, including
 * bool options, value options and positional values.
 * @note Positional values are parsed after the options
 */
#pragma once

#include <string>

using namespace std;

namespace lap {

/**
 * Argument expected, here for polimorphism
 */
class Arg {
public:
	/**
	 * Ctor
	 *
	 * @param description Argument description
	 */
	Arg (const string description);

	/**
	 * Virtual dtor
	 */
	virtual ~Arg ();

	/**
	 * Function called when there was a match
	 *
	 * @param argc Number of available arguments
	 * @param argv Available arguments
	 *
	 * @return Number or extra arguments consumed
	 *
	 * @throws Exception if something went wrong (like number of extra arguments
	 *  not met)
	 */
	virtual int match (int argc, char **argv) = 0;

	/// Argument/option description
	string description;
};


/**
 * Options, that may be in any place on argv (non-positional arguments)
 *
 * @note Options may have an alias (like "-h" and "--help")
 */
class Opt : public Arg {
public:
	/**
	 * Ctor
	 *
	 * @param description Argument description
	 * @param alias Arg alias. Default: "" (empty string)
	 */
	Opt (const string description, const string alias = "");

	/// Option alias
	string alias;
};

}
