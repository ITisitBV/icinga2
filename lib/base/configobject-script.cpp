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

#include "base/configobject.hpp"
#include "base/dictionary.hpp"
#include "base/function.hpp"
#include "base/functionwrapper.hpp"
#include "base/scriptframe.hpp"

using namespace icinga;

static void ConfigObjectModifyAttribute(const String& attr, const Value& value)
{
	ScriptFrame *vframe = ScriptFrame::GetCurrentFrame();
	ConfigObject::Ptr self = vframe->Self;
	REQUIRE_NOT_NULL(self);
	return self->ModifyAttribute(attr, value);
}

static void ConfigObjectRestoreAttribute(const String& attr)
{
	ScriptFrame *vframe = ScriptFrame::GetCurrentFrame();
	ConfigObject::Ptr self = vframe->Self;
	REQUIRE_NOT_NULL(self);
	return self->RestoreAttribute(attr);
}

Object::Ptr ConfigObject::GetPrototype()
{
	static Dictionary::Ptr prototype = new Dictionary({
		{ "modify_attribute", new Function("ConfigObject#modify_attribute", ConfigObjectModifyAttribute, { "attr", "value" }, false) },
		{ "restore_attribute", new Function("ConfigObject#restore_attribute", ConfigObjectRestoreAttribute, { "attr", "value" }, false) }
	});

	return prototype;
}

