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
#include <QMainWindow>
#include <QApplication>

#include "memedar/view/menu.hpp"
#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/main_window.hpp"
#include "memedar/view/qt/menu.hpp"


using md::view::qt::menu;

menu::menu(qt::main_window* main_window)
{
	auto quit     {new ui::button {"quit", []() { ::QApplication::quit(); }}};
	auto designer {new ui::button {"add deck", [this]() { go_to_designer(); }}};

	auto box {new ui::box {QBoxLayout::LeftToRight, quit, designer}};

	main_window->setMenuWidget(box);
}
