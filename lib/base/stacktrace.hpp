/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2018 Icinga Development Team (https://icinga.com/)      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef STACKTRACE_H
#define STACKTRACE_H

#include "base/i2-base.hpp"
#include <iosfwd>

namespace icinga
{

/**
 * A stacktrace.
 *
 * @ingroup base
 */
class StackTrace
{
public:
	StackTrace();
#ifdef _WIN32
	explicit StackTrace(PEXCEPTION_POINTERS exi);
#endif /* _WIN32 */

	void Print(std::ostream& fp, int ignoreFrames = 0) const;

	static void StaticInitialize();

private:
	void *m_Frames[64];
	int m_Count;
};

std::ostream& operator<<(std::ostream& stream, const StackTrace& trace);

}

#endif /* UTILITY_H */
