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

#include "BoolOpt.hpp"

namespace lap {

BoolOpt::BoolOpt (const string& name, const string& alias,
		const string& description, bool stop, boolOptFunc callback)
		: Opt (name, alias, description, stop), callback (callback) {}


BoolOpt::BoolOpt (const string& name, const string& description, bool stop,
		boolOptFunc callback)
		: BoolOpt (name, "", description, stop, callback) {}


void BoolOpt::match (int argc, char **argv) {
	return callback ();
}


unsigned int BoolOpt::numExtraArguments () {
	return 0;
}

}

