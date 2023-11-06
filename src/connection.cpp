/**
 * connection.cpp - Contains database connection impl
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#include <db/connection.h>

#include <db/sqlite/connection.h>
#include <db/pg/connection.h>

namespace db
{

class dummy_connection : public i_connection
{
    virtual bool is_ok() const { return false; }
    virtual result get_result() const { return result::Error; }
    virtual const char* get_error_message() { return ""; }
    virtual dbms get_dbms() { return dbms::None; };
};

connection::connection(dbms dbms_, const std::string &conn_info)
{
    switch (dbms_)
    {
#ifdef _USE_SQLITE
        case dbms::SQLite:
            inst = std::unique_ptr<i_connection>(new sqlite::connection(conn_info));
        break;
#endif
#ifdef _USE_PG
        case dbms::PostgreSQL:
            inst = std::unique_ptr<i_connection>(new pg::connection(conn_info));
        break;
#endif
        default:
            inst = std::unique_ptr<i_connection>(new dummy_connection());
        break;
    }
}

connection::~connection()
{
}

bool connection::is_ok() const
{
    return inst->is_ok();
}

result connection::get_result() const
{
    return inst->get_result();
}

const char* connection::get_error_message()
{
    return inst->get_error_message();
}

dbms connection::get_dbms()
{
    return inst->get_dbms();
}

}
