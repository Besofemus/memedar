/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2018 Roman Erdyakov (Linhurdos) <teremdev@gmail.com>

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

#include <boost/signals2.hpp>

#include <QLabel>
#include <QString>
#include <QLineEdit>

#include "memedar/utils/storage.hpp"
#include "memedar/utils/ref_wrapper.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"

#include "memedar/view/lesson.hpp"
#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/lesson_painter.hpp"
#include "memedar/view/qt/lesson.hpp"


using md::view::qt::lesson_painter;

lesson_painter::lesson_painter(const md::model::deck::deck& deck,
                               md::view::qt::lesson& lesson)
	: box       {QBoxLayout::TopToBottom}
	, m_deck    {deck}
	, m_lesson  {lesson}
{ ;}


void lesson_painter::answering_state(const model::card::card& card)
{
	auto question {new QLabel {card.question.text()}};
	auto show {new ui::button {"show"}};
	
	if (card.has_typing()) {
		
		auto edit {new QLineEdit {}};
		auto signal {[this, edit]() { m_lesson.answer_text(edit->text()); }};
		show->attach(signal);
		box::set_widget(question, edit, show);
		
	}
	else {
		
		auto signal {[this]() { m_lesson.answer(); }};
		show->attach(signal);
		box::set_widget(question, show);
		
	}
}

void lesson_painter::marking_state(const model::task::task& task)
{
	const model::card::card& card {task.card.get()};

	auto question {new QLabel {card.question.text()}};
	auto user_answer {new QLabel {task.user_answer}};
	auto answer {new QLabel {card.answer.text()}};

	auto good_intvl {card.interval(m_deck.good_gap())};
	auto easy_intvl {card.interval(m_deck.easy_gap())};

	auto again {new ui::button {"again\n", [this]() { m_lesson.again();}}};

	auto good {new ui::button {"good\n" + QString::number(good_intvl),
	                           [this, good_intvl]()
	                           { m_lesson.done(good_intvl); }}};

	auto easy {new ui::button {"easy\n" + QString::number(easy_intvl),
	                           [this, easy_intvl]()
	                           { m_lesson.done(easy_intvl); }}};

	box::set_widget(question, user_answer, answer);
	box::put_widget(QBoxLayout::LeftToRight, again, good, easy);
}

void lesson_painter::done_state(const model::card::card& card)
{
	auto question {new QLabel {card.question.text()}};
	auto answer {new QLabel {card.answer.text()}};
	box::set_widget(question, answer);
}

void lesson_painter::draw(const model::task::task& task)
{
	switch (task.state) {
	case md::model::task::state::answering: {
		answering_state(task.card);
		break;
	}
	case md::model::task::state::marking: {
		marking_state(task);
		break;
	}
	case md::model::task::state::done: {
		done_state(task.card);
		break;
	}
	}
}