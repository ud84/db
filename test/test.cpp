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
    db::query q(conn);
    q.prepare("select id, name, number from users");
    if (q.step())
    {
        return q.get_int64(0) == 1 &&
            q.get_string(1) == "First User" &&
            q.get_double(2) == 123.456;
    }

    return false;
}

bool test_params_select(db::connection& conn)
{
    db::query q(conn);
    q.prepare("select id, name, number from users where id = ?");
    q.set(0, 2);
    if (q.step())
    {
        return q.get_int64(0) == 2;
    }

    return false;
}

int main(int argc, char *argv[])
{
    db::connection conn(db::dbms::SQLite, "data/sqlite.db");
    
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

    auto params_select_result = test_params_select(conn);
    if (!params_select_result)
    {
        std::cout << "Params select " << dye::light_red("[FAIL]") << std::endl;
        std::cout << conn.get_error_message() << std::endl;
        return 0;
    }
    std::cout << "Params select " << dye::green("[PASS]") << std::endl;

    return 0;
}
