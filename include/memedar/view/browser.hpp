/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov (Linhurdos) <teremdev@gmail.com>

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


#ifndef MEMEDAR_VIEW_BROWSER_HPP
#define MEMEDAR_VIEW_BROWSER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::view {
	class browser;
}


class md::view::browser
{
public:
	virtual void show(std::deque<md::model::deck::deck>& decks) = 0;
	boost::signals2::signal<void(md::model::deck::deck& deck,
	                             md::model::card::card& card)> call_designer {};
	virtual ~browser() = default;
};


#endif // MEMEDAR_VIEW_BROWSER_HPP
