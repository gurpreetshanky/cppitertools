#include <zip.hpp>

#include "test_helpers.hpp"

#include <vector>
#include <tuple>
#include <string>
#include <iterator>
#include <utility>
#include <sstream>

#include "catch.hpp"

using iter::zip;

TEST_CASE("Simple case, same length", "[zip]") {
    using Tu = std::tuple<int, char, double>;
    using ResVec = const std::vector<Tu>;
    std::vector<int> iv {10, 20, 30};
    std::string s{"hey"};
    double arr[] = {1.0, 2.0, 4.0};

    auto z = zip(iv, s, arr);
    ResVec v(std::begin(z), std::end(z));
    ResVec vc {Tu{10, 'h', 1.0}, Tu{20, 'e', 2.0}, Tu{30, 'y', 4.0}};
    REQUIRE( v == vc );
}

TEST_CASE("One empty, all empty", "[zip]") {
    std::vector<int> iv = {1,2,3};
    std::string s{};
    auto z = zip(iv, s);
    REQUIRE_FALSE( std::begin(z) != std::end(z) );
    auto z2 = zip(s, iv);
    REQUIRE_FALSE( std::begin(z2) != std::end(z2) );
}
