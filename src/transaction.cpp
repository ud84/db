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

class dummy_transaction : public i_transaction
{
public:
    virtual result start() { return result::Error; }

    virtual result commit() { return result::Error; }
    virtual result rollback() { return result::Error; }

};

transaction::transaction(connection &connection_)
{
    switch (connection_.get_dbms())
    {
#ifdef _USE_SQLITE
        case dbms::SQLite:
            inst = std::unique_ptr<i_transaction>(new sqlite::transaction(*reinterpret_cast<sqlite::connection*>(connection_.inst.get())));
        break;
#endif
#ifdef _USE_PG
        case dbms::PostgreSQL:
            inst = std::unique_ptr<i_transaction>(new pg::transaction(*reinterpret_cast<pg::connection*>(connection_.inst.get())));
        break;
#endif
        default:
            inst = std::unique_ptr<i_transaction>(new dummy_transaction());
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
