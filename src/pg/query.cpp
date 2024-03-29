/**
 * query.cpp - Contains postgres query wrapper impl
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#ifdef _USE_PG

#include <db/pg/query.h>

namespace db
{

namespace pg
{

query::query(connection &connection__)
    : connection_(connection__), res(nullptr)
{
}

query::~query()
{
    close();
}

result query::prepare(std::string_view sql)
{
    //return static_cast<result>(sqlite3_prepare_v3(connection_.handle, sql.c_str(), static_cast<int>(sql.size()), 0, &stmt, nullptr));
    return result::OK;
}

result query::set(size_t position, int32_t value)
{
    //return static_cast<result>(sqlite3_bind_int(stmt, static_cast<int>(position + 1), value));
    return result::OK;
}

result query::set(size_t position, int64_t value)
{
    //return static_cast<result>(sqlite3_bind_int64(stmt, static_cast<int>(position + 1), value));
    return result::OK;
}

result query::set(size_t position, double value)
{
    //return static_cast<result>(sqlite3_bind_double(stmt, static_cast<int>(position + 1), value));
    return result::OK;
}

result query::set(size_t position, std::string_view value)
{
    //return static_cast<result>(sqlite3_bind_text(stmt, static_cast<int>(position + 1), value.data(), static_cast<int>(value.size()), SQLITE_TRANSIENT));
    return result::OK;
}

result query::set_null(size_t position)
{
    //return static_cast<result>(sqlite3_bind_null(stmt, static_cast<int>(position + 1)));
    return result::OK;
}

bool query::step()
{
    //return sqlite3_step(stmt) == SQLITE_ROW;
    return false;
}

result query::reset()
{
    //return static_cast<result>(sqlite3_reset(stmt));
    return result::OK;
}

int32_t query::get_int32(size_t position)
{
    return 0;// sqlite3_column_int(stmt, static_cast<int>(position));
}

int64_t query::get_int64(size_t position)
{
    //return sqlite3_column_int64(stmt, static_cast<int>(position));
    return 0;
}

double query::get_double(size_t position)
{
    //return sqlite3_column_double(stmt, static_cast<int>(position));
    return 0;
}

std::string query::get_string(size_t position)
{
    if (!get_null(static_cast<int>(position)))
    {
        //return reinterpret_cast<const char*>(sqlite3_column_text(stmt, static_cast<int>(position)));
    }
    return std::string();
}

bool query::get_null(size_t position)
{
    //return sqlite3_column_type(stmt, static_cast<int>(position)) == SQLITE_NULL;
    return false;
}

void query::close()
{
    if (res != nullptr)
    {
        PQclear(res);
        res = nullptr;
    }
}

}

}

#endif
