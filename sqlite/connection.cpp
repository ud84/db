/**
 * connection.cpp - Contains sqlite connection wrapper impl
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#include <db/sqlite/connection.h>

namespace db
{

namespace sqlite
{

connection::connection(const std::string &path)
	: handle(nullptr), result_(result::OK)
{
	result_ = static_cast<result>(sqlite3_open(path.c_str(), &handle));
	sqlite3_busy_timeout(handle, 500);
}

bool connection::is_ok() const
{
	return result_ == result::OK;
}

result connection::get_result() const
{
	return result_;
}

const char* connection::get_error_message()
{
	return sqlite3_errmsg(handle);
}

connection::~connection()
{
	sqlite3_close(handle);
}

}

}
