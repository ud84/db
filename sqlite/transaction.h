/**
 * transaction.h - Contains sqlite transaction wrapper
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#pragma once

#include <db/i_transaction.h>
#include <db/sqlite/connection.h>

namespace db
{

namespace sqlite
{

class transaction : public i_transaction
{
public:
	transaction(connection &connection_);
	~transaction();

	result start();

    virtual result commit();
    virtual result rollback();
	
private:
	connection &connection_;

	bool started;

};

}

}