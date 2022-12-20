/**
 * test.cpp - Contains db test / examples
 *
 * Author: Anton (ud) Golovkov, udattsk@gmail.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Official repository: https://github.com/ud84/db
 */

#include <iostream>

#include "color_console.hpp"

#include <db/connection.h>
#include <db/transaction.h>
#include <db/query.h>

bool test_connect(db::connection& conn)
{
    return conn.is_ok();
}

bool test_simple_select(db::connection& conn)
{
    return false;
}

int main(int argc, char *argv[])
{
    db::connection conn(db::dbms::SQLite, "D:\\tdlib\\dbaaa.sqlite");
    
    auto conn_result = test_connect(conn);
    if (!conn_result)
    {
        std::cout << "Connection " << dye::light_red("[FAIL]") << std::endl;
        std::cout << conn.get_error_message() << std::endl;
        return 0;
    }
    std::cout << "Connection " << dye::green("[PASS]") << std::endl;

    auto simple_select_result = test_simple_select(conn);
    if (!simple_select_result)
    {
        std::cout << "Simple select " << dye::light_red("[FAIL]") << std::endl;
        std::cout << conn.get_error_message() << std::endl;
        return 0;
    }
    std::cout << "Simple select " << dye::green("[PASS]") << std::endl;

    return 0;
}
