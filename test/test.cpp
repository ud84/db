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

#ifdef _USE_PG

#pragma comment(lib, "libpq.lib")
#pragma comment(lib, "postgres.lib")

#endif

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

bool test_int32_param(db::connection& conn)
{
    db::query q(conn);
    q.prepare("select id, name, number from users where id = ?");
    q.set(0, static_cast<int32_t>(2));
    if (q.step())
    {
        return q.get_int64(0) == 2;
    }

    return false;
}

bool test_int64_param(db::connection& conn)
{
    db::query q(conn);
    q.prepare("select id, name, number from users where id = ?");
    q.set(0, 123123123456789);
    if (q.step())
    {
        return q.get_string(1) == "Big int ID";
    }

    return false;
}

bool test_double_param(db::connection& conn)
{
    db::query q(conn);
    q.prepare("select id, name, number from users where number = ?");
    q.set(0, 123.456);
    if (q.step())
    {
        return q.get_int64(0) == 1;
    }

    return false;
}

bool test_string_param(db::connection& conn)
{
    db::query q(conn);
    q.prepare("select id, name, number from users where name = ?");
    q.set(0, "Second User");
    if (q.step())
    {
        return q.get_int64(0) == 2;
    }

    return false;
}

bool test_transaction(db::connection& conn)
{
    db::query q(conn);
    q.prepare("select id, name, number from users where name = ?");
    q.set(0, "Second User");
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

    auto int32_param_result = test_int32_param(conn);
    if (!int32_param_result)
    {
        std::cout << "Int32 param " << dye::light_red("[FAIL]") << std::endl;
        std::cout << conn.get_error_message() << std::endl;
        return 0;
    }
    std::cout << "Int32 param " << dye::green("[PASS]") << std::endl;

    auto int64_param_result = test_int64_param(conn);
    if (!int64_param_result)
    {
        std::cout << "Int64 param " << dye::light_red("[FAIL]") << std::endl;
        std::cout << conn.get_error_message() << std::endl;
        return 0;
    }
    std::cout << "Int64 param " << dye::green("[PASS]") << std::endl;

    auto double_param_result = test_double_param(conn);
    if (!double_param_result)
    {
        std::cout << "Double param " << dye::light_red("[FAIL]") << std::endl;
        std::cout << conn.get_error_message() << std::endl;
        return 0;
    }
    std::cout << "Double param " << dye::green("[PASS]") << std::endl;

    auto string_param_result = test_string_param(conn);
    if (!string_param_result)
    {
        std::cout << "String param " << dye::light_red("[FAIL]") << std::endl;
        std::cout << conn.get_error_message() << std::endl;
        return 0;
    }
    std::cout << "String param " << dye::green("[PASS]") << std::endl;

    return 0;
}
