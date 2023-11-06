/**
 * connection.cpp - Contains postgres connection wrapper impl
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#ifdef _USE_PG

#include <db/pg/connection.h>

namespace db
{

namespace pg
{

connection::connection(const std::string &conninfo)
    : conn(nullptr), result_(result::OK)
{
    conn = PQconnectdb(conninfo.c_str());
    result_ = PQstatus(conn) == CONNECTION_OK ? result::OK : result::Error;
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
    return PQerrorMessage(conn);
}

connection::~connection()
{
    PQfinish(conn);
}

}

}

#endif
