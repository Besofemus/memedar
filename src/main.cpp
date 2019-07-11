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


#include <memory>
#include <filesystem>
#include <boost/signals2.hpp>
#include <deque>

#include <sqlite3.h>
#include <QString>
#include <QApplication>
#include <QMainWindow>
#include <QScopedPointer>

#include "memedar/utils/storage.hpp"
#include "memedar/utils/ref_wrapper.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/visitor.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/model/dal/transaction.hpp"
#include "memedar/model/dal/card_mapper.hpp"
#include "memedar/model/dal/deck_mapper.hpp"
#include "memedar/model/dal/task_mapper.hpp"

#include "memedar/view/qt/ui/box.hpp"

#include "memedar/view/qt/error_delegate.hpp"
#include "memedar/model/dal/sqlite/adapter.hpp"
#include "memedar/model/dal/sqlite/transaction.hpp"
#include "memedar/model/dal/sqlite/card_mapper.hpp"
#include "memedar/model/dal/sqlite/deck_mapper.hpp"
#include "memedar/model/dal/sqlite/task_mapper.hpp"

#include "memedar/model/card_service.hpp"
#include "memedar/model/deck_service.hpp"
#include "memedar/model/task_service.hpp"

#include "memedar/view/lobby.hpp"
#include "memedar/view/menu.hpp"
#include "memedar/view/designer.hpp"
#include "memedar/view/lesson.hpp"
#include "memedar/view/qt/main_window.hpp"
#include "memedar/view/qt/menu.hpp"
#include "memedar/view/qt/lobby.hpp"
#include "memedar/view/qt/designer.hpp"
#include "memedar/view/qt/lesson.hpp"

#include "memedar/presenter/controller.hpp"

int main(int argc, char *argv[])
{
	QApplication app {argc, argv};

	auto db {md::model::dal::sqlite::adapter::open_sqlite("memedar.db")};

	auto qt_error {std::make_unique<md::view::qt::error_delegate>()};
	auto transact {std::make_unique<md::model::dal::sqlite::transaction>(db)};
	auto c_mapper {std::make_unique<md::model::dal::sqlite::card_mapper>(db)};
	auto d_mapper {std::make_unique<md::model::dal::sqlite::deck_mapper>(db)};
	auto t_mapper {std::make_unique<md::model::dal::sqlite::task_mapper>(db)};

	md::model::card_service card_service {*qt_error, *transact, *c_mapper};
	md::model::deck_service deck_service {*qt_error, *transact, *c_mapper, *d_mapper};
	md::model::task_service task_service {*qt_error, *transact, *c_mapper, *d_mapper, *t_mapper};

	auto main_window {new md::view::qt::main_window {}};
	auto menu     {std::make_unique<md::view::qt::menu>(main_window)};
	auto lobby    {std::make_unique<md::view::qt::lobby>(main_window)};
	auto designer {std::make_unique<md::view::qt::designer>(main_window)};
	auto lesson   {std::make_unique<md::view::qt::lesson>(main_window)};
	main_window->show();

	md::controller controller {card_service, deck_service, task_service,
	                           *menu, *lobby, *lesson, *designer};

	return app.exec();
}
