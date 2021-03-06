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

#include "Opt.hpp"
#include "BoolOpt.hpp"
#include "StrOpt.hpp"

#include <unordered_map>

using namespace std;

namespace lap {

/**
 * How to store the expected options
 * @note With this construction, we can have option aliases
 */
using OptMap = unordered_map<string, Opt *>;


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
	 * Dtor: delete known Opts
	 */
	~ArgParser ();

	/**
	 * Parse the command line options passed
	 *
	 * @param argc Number of arguments passed
	 * @param argv Array of arguments
	 *
	 * @return Vector with the unmatched arguments (including program name)
	 *
	 * @throw lap::Exception if there were not enough arguments for some option
	 * @throw Whatever callback throws
	 */
	argVector parse (int argc, char **argv);
	/**
	 * Parse the command line options, excluding matched options from args
	 *
	 * @note This function is well suited to those who already have some
	 *  'argc + argv' logic and don't want to use a vector
	 * @note This method calls @ref parse inside, so params and exceptions are
	 *  the same
	 *
	 * @param argc Number of arguments passed
	 * @param argv Array of arguments
	 *
	 * @sa parse
	 */
	void parseAndRemove (int& argc, char **& argv);

	/**
	 * Register a BoolOpt, with custom description and no argument callback
	 *
	 * @warning Option string doesn't include "-" or "--" or "/", do it on your
	 *  own
	 *
	 * @param option Option string
	 * @param description Custom description, for usage printing
	 * @param callback Function called when option is matched
	 * @param optionAlias Option alias
	 */
	void on (const string& option, const string& optionAlias,
			const string& description, boolOptFunc callback);
	/**
	 * Register BoolOpt overload without option alias
	 *
	 * @sa on
	 */
	void on (const string& option, const string& description,
			boolOptFunc callback);

	/**
	 * Register a BoolOpt, with custom description and no argument callback,
	 * stopping parse after match
	 *
	 * @warning Option string doesn't include "-" or "--" or "/", do it on your
	 *  own
	 *
	 * @param option Option string
	 * @param description Custom description, for usage printing
	 * @param callback Function called when option is matched
	 * @param optionAlias Option alias
	 */
	void stopOn (const string& option, const string& optionAlias,
			const string& description, boolOptFunc callback);
	/**
	 * Register BoolOpt overload without option alias, stopping parse after
	 * match
	 *
	 * @sa stopOn
	 */
	void stopOn (const string& option, const string& description,
			boolOptFunc callback);

	/**
	 * Register a StrOpt, with custom description and N argument callback
	 *
	 * @warning Option string doesn't include "-" or "--" or "/", do it on your
	 *  own
	 * @warning If numArgs is 0, the option won't receive any argument __EVER__
	 *
	 * @param option Option string
	 * @param description Custom description, for usage printing
	 * @param n Number of needed arguments for option
	 * @param argNames Names of the arguments, for documentation
	 * @param callback Function called when option is matched
	 * @param optionAlias Option alias
	 */
	void on (const string& option, const string& optionAlias,
			const string& description, unsigned int n,
			initializer_list<string> argNames, strOptFunc callback);
	/**
	 * Register StrOpt overload without option alias
	 */
	void on (const string& option, const string& description,
			unsigned int n, initializer_list<string> argNames, strOptFunc callback);

	/**
	 * Register a StrOpt, with custom description and N argument callback,
	 * stopping parse after match
	 *
	 * @warning Option string doesn't include "-" or "--" or "/", do it on your
	 *  own
	 * @warning If numArgs is 0, the option won't receive any argument __EVER__
	 *
	 * @param option Option string
	 * @param description Custom description, for usage printing
	 * @param n Number of needed arguments for option
	 * @param argNames Names of the arguments, for documentation
	 * @param callback Function called when option is matched
	 * @param optionAlias Option alias
	 */
	void stopOn (const string& option, const string& optionAlias,
			const string& description, unsigned int n,
			initializer_list<string> argNames, strOptFunc callback);
	/**
	 * Register StrOpt overload without option alias, stopping parse after match
	 */
	void stopOn (const string& option, const string& description,
			unsigned int n, initializer_list<string> argNames, strOptFunc callback);

	/**
	 * Show argument help, based on registered options
	 *
	 * Message will be in the format:
	 * ```
	 * $prefix
	 * OPTIONS:
	 *     $option|$alias $argN... : $description
	 *     ...
	 * Any arguments are mandatory
	 *
	 * $sufix
	 * ```
	 *
	 * @param prefix String prefix to be written before default string
	 * @param sufix String sufix to be written after default string
	 */
	void showHelp (const string& prefix, const string& sufix);

private:
	/**
	 * A map of the registered arguments
	 */
	OptMap knownOpts;

	/**
	 * Register of BoolOpts, private for 'stop' abstraction
	 */
	void registerOpt (const string& option, const string& optionAlias,
		const string& description, bool stop, boolOptFunc callback);
	/**
	 * Register of StrOpts, private for 'stop' abstraction
	 */
	void registerOpt (const string& option, const string& optionAlias,
			const string& description, bool stop, unsigned int n,
			initializer_list<string> argNames, strOptFunc callback);
};

}
