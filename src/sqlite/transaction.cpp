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

#include <db/sqlite/transaction.h>

namespace db
{

namespace sqlite
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
    return static_cast<result>(sqlite3_exec(connection_.handle, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr));
}

result transaction::commit()
{
    started = false;
    return static_cast<result>(sqlite3_exec(connection_.handle, "COMMIT;", nullptr, nullptr, nullptr));
}

result transaction::rollback()
{
    started = false;
    return static_cast<result>(sqlite3_exec(connection_.handle, "ROLLBACK;", nullptr, nullptr, nullptr));
}

}

}
