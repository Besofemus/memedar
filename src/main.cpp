/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2018-2019 Roman Erdyakov

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


#include <QApplication>


#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/taskbook.hpp"
#include "memedar/model/service/service.hpp"
#include "memedar/model/dal/mapper.hpp"

#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/error_delegate.hpp"
#include "memedar/view/qt/error_delegate.hpp"

#include "memedar/view/lobby.hpp"
#include "memedar/view/menu.hpp"
#include "memedar/view/designer.hpp"
#include "memedar/view/lesson.hpp"
#include "memedar/view/browser.hpp"
#include "memedar/view/qt/main_window.hpp"
#include "memedar/view/qt/menu.hpp"
#include "memedar/view/qt/lobby.hpp"
#include "memedar/view/qt/designer.hpp"
#include "memedar/view/qt/lesson.hpp"
#include "memedar/view/qt/browser.hpp"

#include "memedar/presenter/controller.hpp"


int main(int argc, char *argv[])
{
	QApplication app {argc, argv};
	
	auto qt_error {std::make_unique<md::view::qt::error_delegate>()};
	
	try {
		md::model::dal::mapper mapper {md::model::dal::make_sqlite("memedar.db")};
		md::model::service service {mapper};

		auto main_window {new md::view::qt::main_window {}};
		auto menu     {std::make_unique<md::view::qt::menu>(main_window)};
		auto lobby    {std::make_unique<md::view::qt::lobby>(main_window)};
		auto designer {std::make_unique<md::view::qt::designer>(main_window)};
		auto lesson   {std::make_unique<md::view::qt::lesson>(main_window)};
		auto browser  {std::make_unique<md::view::qt::browser>(main_window)};
		main_window->show();

		md::controller controller {service, *qt_error,
		                           *menu, *lobby, *lesson, *designer, *browser};
	}
	catch (std::system_error& e) {
		qt_error->show_error(e);
	}
	
	return app.exec();
}
