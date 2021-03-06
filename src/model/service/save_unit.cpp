/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov

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


#include <deque>


#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/taskbook.hpp"

#include "memedar/model/dal/transaction_guard.hpp"
#include "memedar/model/dal/mapper.hpp"

#include "memedar/model/service/save_unit.hpp"


using md::model::save_unit;

save_unit::save_unit(dal::mapper& mapper)
	: deck_to_taskbook {mapper}
	, m_mapper {mapper}
{ ;}


void save_unit::save_card(deck::deck& deck, card::card_dto&& new_card)
{
	decltype(auto) transaction {m_mapper.make_transaction()};
	
	m_mapper.card->save_card(deck, std::move(new_card));

	transaction.commit();
}

void save_unit::save_deck(deck::deck_value&& deck_value)
{
	decltype(auto) transaction {m_mapper.make_transaction()};
		
	decltype(auto) deck {m_mapper.deck->save_deck(std::move(deck_value))};
	
	deck.need_cards.connect([this](deck::deck& deck)
	                        {
		                        decltype(auto) transaction {m_mapper.make_transaction()};
		                        decltype(auto) boss {deck.get_storage_boss()};
		                        
		                        m_mapper.card->load_cards(deck);
		                        
		                        boss.commit();
		                        transaction.commit();
	                        });
	
	deck_to_taskbook::add_deck(std::move(deck));


	transaction.commit();
}

