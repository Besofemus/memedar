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


#ifndef MEMEDAR_CONTROLLER_HPP
#define MEMEDAR_CONTROLLER_HPP


namespace md {
	class menu_presenter;
	class lobby_presenter;
	class designer_presenter;
	class lesson_presenter;
	class controller;
}


class md::controller
{
public:
	controller(md::menu_presenter& menu,
	           md::lobby_presenter& lobby,
	           md::designer_presenter& designer,
	           md::lesson_presenter& lesson);
protected:
	md::menu_presenter& m_menu;
	md::lobby_presenter& m_lobby;
	md::designer_presenter& m_designer;
	md::lesson_presenter& m_lesson;
};

#endif // MEMEDAR_CONTROLLER_HPP
