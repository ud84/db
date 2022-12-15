/**
 * query.h - Contains sqlite query wrapper
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#pragma once

#include <cstdint>
#include <string>

#include <db/i_query.h>
#include <db/sqlite/connection.h>

namespace db
{

namespace sqlite
{

class query : public i_query
{
public:
	query(connection &connection_);
	~query();

    virtual result prepare(const std::string &sql);
    virtual result set(size_t position, int32_t value);
    virtual result set(size_t position, int64_t value);
    virtual result set(size_t position, double value);
    virtual result set(size_t position, const std::string &value);
    virtual result set_null(size_t position);

    virtual bool step();
    virtual result reset();

    virtual int32_t get_int32(size_t position);
    virtual int64_t get_int64(size_t position);
    virtual double get_double(size_t position);
    virtual std::string get_string(size_t position);
    virtual bool get_null(size_t position);

    virtual void close();

private:
	connection &connection_;
	sqlite3_stmt *stmt;
};

}

}
