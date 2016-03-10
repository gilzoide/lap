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

/** @file Exception.hpp
 * lap's exceptions
 */
#pragma once

#include <string>
#include <sstream>
#include <exception>

using namespace std;

namespace lap {

/// Auxiliary macro for API to tell us where the problem ocurred
#define LAP_API_EXCEPTION(funcName, what) \
	[&] () -> Exception { \
		ostringstream os; \
		os << "[lap::" << funcName << " @ " __FILE__ << ':' << __LINE__ \
				<< "] " << what << endl; \
		return move (Exception (os.str ())); \
	} () \

/**
 * Lap's API exceptions
 */
class Exception : public exception {
public:
	/**
	 * Ctor
	 *
	 * @param what_arg Explanatory string
	 */
	Exception (const string& what_arg);
	/**
	 * Ctor
	 *
	 * @param what_arg Explanatory string
	 */
	Exception (const char *what_arg);

	/**
	 * Returns the explanatory string
	 *
	 * @return Explanatory string
	 */
	const char *what () const noexcept override;

private:
	/// The explanatory string
	string what_arg;
};

}
