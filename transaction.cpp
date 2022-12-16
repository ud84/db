/**
 * transaction.cpp - Contains database transaction impl
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#include <db/transaction.h>

#include <db/sqlite/transaction.h>
#include <db/pg/transaction.h>

namespace db
{

transaction::transaction(connection &connection_)
{
    switch (connection_.get_dbms())
    {
        case dbms::SQLite:
            inst = std::unique_ptr<sqlite::transaction>(new sqlite::transaction(*reinterpret_cast<sqlite::connection*>(connection_.inst.get())));
        break;
        case dbms::PostgreSQL:
            inst = std::unique_ptr<pg::transaction>(new pg::transaction(*reinterpret_cast<pg::connection*>(connection_.inst.get())));
        break;
    }
}

transaction::~transaction()
{
}

result transaction::start()
{
    return inst->start();
}

result transaction::commit()
{
    return inst->commit();
}

result transaction::rollback()
{
    return inst->rollback();
}

}
