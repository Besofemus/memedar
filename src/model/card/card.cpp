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


#include <ctime>
#include <memory>

#include <QString>

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/card/visitor.hpp"
#include "memedar/model/card/type.hpp"


using md::model::card::card;

card::card(side::side&& question_side,
           side::side&& answer_side,
           bool typing)
	: identity       {identity {}}
	, card::schedule {card::schedule {}}
	, card::interval {card::interval {}}
	, question       {std::move(question_side)}
	, answer         {std::move(answer_side)}
	, m_typing       {typing}
	, m_type         {nullptr}
{ ;}

card::card(identity id,
           card::schedule schedule,
           card::interval interval,
           side::side&& question_side,
           side::side&& answer_side,
           bool typing)
	: identity       {id}
	, card::schedule {schedule}
	, card::interval {interval}
	, question       {std::move(question_side)}
	, answer         {std::move(answer_side)}
	, m_typing       {typing}
	, m_type         {nullptr}
{ ;}

bool card::has_typing() const
{
	return m_typing;
}

void card::set_type(std::shared_ptr<md::model::card::type> type)
{
	m_type = type;
}

void card::take_visitor(md::model::card::visitor& visitor)
{
	m_type->accept(visitor);
}
