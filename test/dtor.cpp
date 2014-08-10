// Eggs.Variant
//
// Copyright Agustin K-ballo Berge, Fusion Fenix 2014
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <eggs/variant.hpp>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "dtor.hpp"

struct Y
{
    Y() = default;
    Y(Y const&) {};
    ~Y() = default;
};

TEST_CASE("variant<Ts...>::~variant()", "[variant.dtor]")
{
    {
        {
            eggs::variant<int, Dtor> v;
            v.emplace<Dtor>();

            REQUIRE(std::is_trivially_destructible<decltype(v)>::value == false);

            REQUIRE(Dtor::called == false);
        }
        REQUIRE(Dtor::called == true);
    }
    Dtor::called = false;

    SECTION("trivially_destructible")
    {
        eggs::variant<int, Y> v1;
        eggs::variant<int, float> v2;

        REQUIRE(std::is_trivially_destructible<decltype(v1)>::value == true);
        REQUIRE(std::is_trivially_destructible<decltype(v2)>::value == true);
    }
}