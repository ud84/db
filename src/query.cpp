/**
 * query.cpp - Contains database query impl
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#include <db/query.h>

#include <db/sqlite/query.h>
#include <db/pg/query.h>

namespace db
{

class dummy_query : public i_query
{
public:
    virtual result prepare(std::string_view) { return result::Error; }
    virtual result set(size_t, int32_t) { return result::Error; }
    virtual result set(size_t, int64_t) { return result::Error; }
    virtual result set(size_t, double) { return result::Error; }
    virtual result set(size_t, std::string_view) { return result::Error; }
    virtual result set_null(size_t) { return result::Error; }

    virtual bool step() { return false; }
    virtual result reset() { return result::Error; }

    virtual int32_t get_int32(size_t) { return 0; }
    virtual int64_t get_int64(size_t) { return 0; }
    virtual double get_double(size_t) { return 0.; }
    virtual std::string get_string(size_t) { return ""; }
    virtual bool get_null(size_t) { return false; }

    virtual void close() {}
};


query::query(connection &connection_)
{
    switch (connection_.get_dbms())
    {
#ifdef _USE_SQLITE
        case dbms::SQLite:
            inst = std::unique_ptr<i_query>(new sqlite::query(*reinterpret_cast<sqlite::connection*>(connection_.inst.get())));
        break;
#endif
#ifdef _USE_PG
        case dbms::PostgreSQL:
            inst = std::unique_ptr<i_query>(new pg::query(*reinterpret_cast<pg::connection*>(connection_.inst.get())));
        break;
#endif
        default:
            inst = std::unique_ptr<i_query>(new dummy_query());
        break;
    }
}

query::~query()
{
}

result query::prepare(std::string_view sql)
{
    return inst->prepare(sql);
}

result query::set(size_t position, int32_t value)
{
    return inst->set(position, value);
}

result query::set(size_t position, int64_t value)
{
    return inst->set(position, value);
}

result query::set(size_t position, double value)
{
    return inst->set(position, value);
}

result query::set(size_t position, std::string_view value)
{
    return inst->set(position, value);
}

result query::set_null(size_t position)
{
    return inst->set_null(position);
}

bool query::step()
{
    return inst->step();
}

result query::reset()
{
    return inst->reset();
}

int32_t query::get_int32(size_t position)
{
    return inst->get_int32(position);
}

int64_t query::get_int64(size_t position)
{
    return inst->get_int64(position);
}

double query::get_double(size_t position)
{
    return inst->get_double(position);
}

std::string query::get_string(size_t position)
{
    return inst->get_string(position);
}

bool query::get_null(size_t position)
{
    return inst->get_null(position);
}

void query::close()
{
    inst->close();
}

}
