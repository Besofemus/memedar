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
#include <deque>

#include <QString>
#include <boost/signals2.hpp>

#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/taskbook.hpp"
#include "memedar/model/service/service.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/view/lobby.hpp"

#include "memedar/presenter/presenter.hpp"
#include "memedar/presenter/lobby_presenter.hpp"
#include "memedar/presenter/controller.hpp"


using md::lobby_presenter;

lobby_presenter::lobby_presenter(md::controller& controller,
                                 md::model::service& service,
                                 md::view::error_delegate& error_delegate,
                                 md::view::lobby& lobby)
	: m_controller     {controller}
	, m_service        {service}
	, m_error_delegate {error_delegate}
	, m_lobby          {lobby}
{
	auto lesson   {[this](model::deck::deck& deck) { m_controller.run_lesson(deck); }};
	auto add_card {[this](model::deck::deck& deck) { m_controller.add_card(deck); }};
	auto upd_deck {[this](model::deck::deck& deck) { m_controller.update_deck(deck); }};
	auto del_deck {[this](model::deck::deck& deck) { delete_deck(deck); }};
	
	add_connect(m_lobby.call_lesson.connect(lesson),
	            m_lobby.add_card.connect(add_card),
	            m_lobby.update_deck.connect(upd_deck),
	            m_lobby.delete_deck.connect(del_deck));
	
	run();
}

void lobby_presenter::run()
{
	m_lobby.show(m_service.get_decks());
}

void lobby_presenter::delete_deck(model::deck::deck& deck)
{
	try {
		m_service.delete_deck(deck);
		run();
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}
