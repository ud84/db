/**
 * transaction.cpp - Contains sqlite transaction wrapper impl
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#include <db/pg/transaction.h>

namespace db
{

namespace pg
{


transaction::transaction(connection &connection__)
    : connection_(connection__), started(false)
{
}

transaction::~transaction()
{
    if (started)
    {
        rollback();
    }
}

result transaction::start()
{
    started = true;
    auto res = PQexec(connection_.conn, "BEGIN");
    if (!res || PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PQclear(res);
        return result::Error;
    }
    PQclear(res);
    return result::OK;
}

result transaction::commit()
{
    started = false;
    auto res = PQexec(connection_.conn, "COMMIT");
    if (!res || PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PQclear(res);
        return result::Error;
    }
    PQclear(res);
    return result::OK;
}

result transaction::rollback()
{
    started = false;
    auto res = PQexec(connection_.conn, "ROLLBACK");
    if (!res || PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PQclear(res);
        return result::Error;
    }
    PQclear(res);
    return result::OK;
}

}

}
