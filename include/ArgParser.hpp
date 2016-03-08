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

/** @file ArgParser.hpp
 * Command Line argument parser, intended for parsing _argc + argv_ style
 * arguments
 */
#pragma once

#include <Arg.hpp>
#include <BoolOpt.hpp>
#include <StrOpt.hpp>

#include <map>
#include <functional>

using namespace std;

namespace lap {

/**
 * How to store the expected options
 * @note With this construction, we can have option aliases
 */
using OptMap = map<string, Opt *>;


/**
 * A command line argument parser
 *
 * It can extract arguments from the ones passed 
 */
class ArgParser {
public:
	/**
	 * Default Ctor
	 */
	ArgParser ();

	/**
	 * Dtor: delete Opts
	 */
	~ArgParser ();

	/**
	 * Parse the command line options passed
	 *
	 * @param argc Number of arguments passed
	 * @param argv Array of arguments
	 */
	void parse (int argc, char **argv);

	/**
	 * Expect a BoolArg, with custom description and no argument callback
	 *
	 * @warning Option string doesn't include "-" or "--" or "/", do it on your
	 *  own
	 *
	 * @param option Option string
	 * @param description Custom description, for usage printing
	 * @param callback Function called when option is matched
	 * @param optionAlias Option alias
	 */
	void expect (const string& option, const string& description,
			boolOptFunc callback, const string& optionAlias = "");

	/**
	 * Expect a StrArg, with custom description and N argument callback
	 *
	 * @warning Option string doesn't include "-" or "--" or "/", do it on your
	 *  own
	 *
	 * @param option Option string
	 * @param description Custom description, for usage printing
	 * @param numArgs Number of needed arguments for option
	 * @param callback Function called when option is matched
	 * @param optionAlias Option alias
	 */
	void expect (const string& option, const string& description, int n,
			strOptFunc callback, const string& optionAlias = "");

private:
	/**
	 * A map of the expected arguments
	 */
	OptMap knownOpts;
};

}
