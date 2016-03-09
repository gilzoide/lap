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

#include <Arg.hpp>

#include <string>

using namespace std;

namespace lap {

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
	 * @param name Argument name
	 * @param alias Opt alias
	 * @param description Argument description
	 */
	Opt (const string& name, const string& alias, const string& description);
	/**
	 * Ctor overload without alias
	 */
	Opt (const string& name, const string& description);

	/**
	 * Still, the match function
	 */
	virtual bool match (int argc, char **argv) = 0;

	/**
	 * Still, the numExtraArguments function
	 */
	virtual unsigned int numExtraArguments () = 0;

	/// Option alias
	string alias;
};

}

