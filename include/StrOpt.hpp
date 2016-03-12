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

/** @file StrOpt.hpp
 * Option that needs aditional arguments (here, given as strings)
 */
#pragma once

#include "Opt.hpp"

#include <functional>
#include <vector>

namespace lap {

/// String Option callback function: expects it's N arguments on a vector
using strOptFunc = function<bool (vector <const char *>)>;

/**
 * String option, those who expect N arguments
 */
class StrOpt : public Opt {
public:
	/**
	 * Ctor
	 *
	 * @param name Argument name
	 * @param alias Option alias
	 * @param description Option description
	 * @param n Number of expected arguments
	 * @param argNames Names of the arguments, for documentation
	 * @param callback Function to be called when option is matched
	 */
	StrOpt (const string& name, const string& alias, const string& description,
			int n, initializer_list<string> argNames, strOptFunc callback);
	/**
	 * Ctor overload without alias
	 */
	StrOpt (const string& name, const string& description, int n,
			initializer_list<string> argNames, strOptFunc callback);
	
	/**
	 * There was a match: call callback with the following args
	 */
	bool match (int argc, char **argv) override;

	/**
	 * Extra arguments expected
	 *
	 * @return n
	 */
	unsigned int numExtraArguments () override;

	/**
	 * Opt::getUsage function, including argument names
	 *
	 * @return Option with arguments usage string
	 */
	string getUsage () override;

	/// Number of arguments expected
	int n;

	/// The argument names
	vector<string> argNames;

	/**
	 * Callback to be called when option is found
	 */
	strOptFunc callback;
};


}

