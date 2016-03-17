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

#include "StrOpt.hpp"

#include <sstream>

namespace lap {

StrOpt::StrOpt (const string& name, const string& alias,
		const string& description, int n, initializer_list<string> argNames,
		strOptFunc callback)
		: Opt (name, alias, description), n (n), argNames (argNames),
		callback (callback) {}


StrOpt::StrOpt (const string& name, const string& description, int n,
		initializer_list<string> argNames, strOptFunc callback)
		: StrOpt (name, "", description, n, argNames, callback) {}


bool StrOpt::match (int argc, char **argv) {
	// skip option name argument
	argv++;
	argVector v (argv, argv + n);
	return callback (move (v));
}


unsigned int StrOpt::numExtraArguments () {
	return n;
}


string StrOpt::getUsage () {
	ostringstream os;
	os << Opt::getUsage ();
	// argument names
	for (auto & arg : argNames) {
		os << ' ' << arg;
	}
	return move (os.str ());
}

}
