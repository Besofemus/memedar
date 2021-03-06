/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2018 Roman Erdyakov

 * This file is part of Memedar (flashcard system)
 * Memedar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include <cstdint>

#include <QString>

#include "memedar/model/side/side.hpp"

using md::model::side::side_value;

side_value::side_value(QString&& text)
	: m_text   {std::move(text)}
{ ;}

side_value::side_value(side_value&& other)
	: m_text   {std::move(other.m_text)}
{ ;}

side_value& side_value::operator=(side_value&& other)
{
	if (this != &other) {
		m_text = std::move(other.m_text);
	}
	return *this;
}

const QString& side_value::text() const
{
	return m_text;
}

using md::model::side::side;

side::side(identity id, side::side_value&& value)
	: identity   {id}
	, side_value {std::move(value)}
{ ;}

md::model::side::side& side::operator=(md::model::side::side_value&& value)
{
	side_value::operator=(std::move(value));
	return *this;
}
