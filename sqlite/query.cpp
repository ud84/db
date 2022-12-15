/**
 * query.cpp - Contains sqlite query wrapper impl
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#include <db/sqlite/query.h>

namespace db
{

namespace sqlite
{

query::query(connection &connection__)
	: connection_(connection__), stmt(nullptr)
{
}

query::~query()
{
	close();
}

result query::prepare(const std::string &sql)
{
	return static_cast<result>(sqlite3_prepare_v3(connection_.handle, sql.c_str(), static_cast<int>(sql.size()), 0, &stmt, nullptr));
}

result query::set(size_t position, int32_t value)
{
	return static_cast<result>(sqlite3_bind_int(stmt, static_cast<int>(position + 1), value));
}

result query::set(size_t position, int64_t value)
{
	return static_cast<result>(sqlite3_bind_int64(stmt, static_cast<int>(position + 1), value));
}

result query::set(size_t position, double value)
{
	return static_cast<result>(sqlite3_bind_double(stmt, static_cast<int>(position + 1), value));
}

result query::set(size_t position, const std::string &value)
{
	return static_cast<result>(sqlite3_bind_text(stmt, static_cast<int>(position + 1), value.data(), static_cast<int>(value.size()), SQLITE_TRANSIENT));
}

result query::set_null(size_t position)
{
	return static_cast<result>(sqlite3_bind_null(stmt, static_cast<int>(position + 1)));
}

bool query::step()
{
	return sqlite3_step(stmt) == SQLITE_ROW;
}

result query::reset()
{
	return static_cast<result>(sqlite3_reset(stmt));
}

int32_t query::get_int32(size_t position)
{
	return sqlite3_column_int(stmt, static_cast<int>(position));
}

int64_t query::get_int64(size_t position)
{
	return sqlite3_column_int64(stmt, static_cast<int>(position));
}

double query::get_double(size_t position)
{
	return sqlite3_column_double(stmt, static_cast<int>(position));
}

std::string query::get_string(size_t position)
{
	if (!get_null(static_cast<int>(position)))
	{
		return reinterpret_cast<const char*>(sqlite3_column_text(stmt, static_cast<int>(position)));
	}
	return std::string();
}

bool query::get_null(size_t position)
{
	return sqlite3_column_type(stmt, static_cast<int>(position)) == SQLITE_NULL;
}

void query::close()
{
	if (stmt != nullptr)
	{
		sqlite3_finalize(stmt);
		stmt = nullptr;
	}
}

}

}
