#include <combinations_with_replacement.hpp>

#include <iterator>
#include <string>
#include <set>
#include <vector>

#include "helpers.hpp"
#include "catch.hpp"

using iter::combinations_with_replacement;
using itertest::BasicIterable;
using CharCombSet = std::vector<std::vector<char>>;

TEST_CASE("combinations_with_replacement: Simple combination",
        "[combinations_with_replacement]") {
    std::string s{"ABC"};
    CharCombSet sc;
    for (auto v : combinations_with_replacement(s, 2)) {
        sc.emplace_back(std::begin(v), std::end(v));
    }
    CharCombSet ans =
        {{'A','A'}, {'A','B'}, {'A','C'}, {'B','B'}, {'B','C'}, {'C','C'}};
    REQUIRE( ans == sc );
}

TEST_CASE("combinations_with_replacement: iterators can be compared",
        "[combinations_with_replacement]") {
    std::string s{"ABCD"};
    auto c = combinations_with_replacement(s, 2);
    auto it = std::begin(c);
    REQUIRE( it == std::begin(c) );
    REQUIRE_FALSE( it != std::begin(c) );
    ++it;
    REQUIRE( it != std::begin(c) );
    REQUIRE_FALSE( it == std::begin(c) );
}

TEST_CASE("combinations_with_replacement: big size is no problem",
        "[combinations_with_replacement]") {
    std::string s{"AB"};
    CharCombSet sc;
    for (auto v : combinations_with_replacement(s, 3)) {
        sc.emplace_back(std::begin(v), std::end(v));
    }
    CharCombSet ans =
        {{'A', 'A', 'A'}, {'A', 'A', 'B'}, {'A', 'B', 'B'}, {'B', 'B', 'B'}};
    REQUIRE( ans == sc );
}
    
TEST_CASE("combinations_with_replacement: 0 size is empty",
        "[combinations_with_replacement]") {
    std::string s{"A"};
    auto cwr = combinations_with_replacement(s, 0);
    REQUIRE( std::begin(cwr) == std::end(cwr) );
}

TEST_CASE("combinations_with_replacement: binds to lvalues, moves rvalues",
        "[combinations_with_replacement]") {
    BasicIterable<char> bi{'x', 'y', 'z'};
    SECTION("binds to lvalues") {
        combinations_with_replacement(bi, 1);
        REQUIRE_FALSE( bi.was_moved_from() );
    }
    SECTION("moves rvalues") {
        combinations_with_replacement(std::move(bi), 1);
        REQUIRE( bi.was_moved_from() );
    }
}

TEST_CASE("combinations_with_replacement: "
        "doesn't move or copy elements of iterable",
        "[combinations_with_replacement]") {
    constexpr itertest::SolidInt arr[] = {{6}, {7}, {8}};
    for (auto&& i : combinations_with_replacement(arr, 1)) {
        (void)i;
    }
}
