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

/** @file BoolOpt.hpp
 * Boolean options
 */
#pragma once

#include <Opt.hpp>

#include <functional>

namespace lap {

using boolOptFunc = function<void ()>;

/**
 * Boolean option, those who don't expect arguments itself
 */
class BoolOpt : public Opt {
public:
	/**
	 * Ctor
	 *
	 * @param description Option description
	 * @param callback Function to be called when option is matched
	 */
	BoolOpt (const string& description, boolOptFunc callback,
			const string& alias = "");
	
	/**
	 * There was a match: call callback
	 */
	int match (int argc, char **argv) override;


	/**
	 * Callback to be called when option is found
	 */
	boolOptFunc callback;
};

}
