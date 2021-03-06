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


#ifndef MEMDAR_PRESENTER_HPP
#define MEMDAR_PRESENTER_HPP


namespace md {
	class presenter;
}


class md::presenter
{
public:
	virtual void run() = 0;
	virtual ~presenter() = default;
protected:
	template<class... C>
	void add_connect(C&&... connections)
	{
		(conn.push_back(std::move(connections)), ...);
	}
	std::vector<boost::signals2::scoped_connection> conn {};
};


#endif // MEMDAR_PRESENTER_HPP
