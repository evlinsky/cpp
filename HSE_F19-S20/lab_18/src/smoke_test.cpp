#include "format.hpp"

#include <string>
#include <vector>

#include <doctest.h>
#include <boost/hana.hpp>

//#define TEST_BOOL
//#define TEST_SFINAE
//#define TEST_VECTOR
//#define TEST_VECTOR_SFINAE
//#define TEST_INTEGRAL
//#define TEST_FORMAT_MEMBER
//#define TEST_FORMAT_MEMBER_SFINAE

namespace {
auto is_formattable = boost::hana::is_valid(
    [](const auto &value)
        -> std::void_t<decltype(format::make_string(value))> {
    }
);
}

#ifdef TEST_BOOL
TEST_CASE("bool") {
    CHECK(format::make_string(true) == "true");
    CHECK(format::make_string(false) == "false");
    static_assert(is_formattable(true));  // Follows previous lines' compilation.
    static_assert(is_formattable(false));
}
#endif

#ifdef TEST_SFINAE
TEST_CASE("Non-formattable") {
    struct {} s;
    CHECK(!is_formattable(s));  // Not static_assert so it's not a compilation error.
    // format::make_string(s);  // Should not compile with a short error.
}
#endif

#ifdef TEST_INTEGRAL
TEST_SUITE("integral") {
TEST_CASE("int") {
    CHECK(format::make_string(0) == "0");
    CHECK(format::make_string(12345) == "12345");
    CHECK(format::make_string(-12345) == "-12345");
}

TEST_CASE("unsigned int") {
    CHECK(format::make_string(0u) == "0");
    CHECK(format::make_string(12345u) == "12345");
}
}
#endif

#ifdef TEST_VECTOR
TEST_SUITE("vector<T>") {
#ifdef TEST_BOOL
TEST_CASE("T=bool") {
    CHECK(format::make_string(std::vector<bool>{}) == "{}");
    CHECK(format::make_string(std::vector{true}) == "{true}");
    CHECK(format::make_string(std::vector{false}) == "{false}");
    CHECK(format::make_string(std::vector{true, false, true, true}) == "{true, false, true, true}");
}
TEST_CASE("T=vector<bool>") {
    CHECK(format::make_string(std::vector<std::vector<bool>>{}) == "{}");
    CHECK(format::make_string(std::vector{
        std::vector{true, false},
        std::vector<bool>{},
        std::vector{true}
    }) == "{{true, false}, {}, {true}}");
}
#endif
#ifdef TEST_INTEGRAL
TEST_CASE("T=int") {
    CHECK(format::make_string(std::vector<int>{}) == "{}");
    CHECK(format::make_string(std::vector{10}) == "{10}");
    CHECK(format::make_string(std::vector{-10, 20, -5}) == "{-10, 20, -5}");
}
#endif
#ifdef TEST_VECTOR_SFINAE
TEST_CASE("T is non-formattable") {
    struct S {};
    std::vector<S> vec(10);
    CHECK(!is_formattable(vec));  // Not static_assert so it's not a compilation error.
    // format::make_string(vec);  // Should not compile with a short error.
}
#endif
}
#endif

#ifdef TEST_FORMAT_MEMBER
TEST_SUITE(".format() member") {
struct S {
    std::string format() const { return "hello"; }
};

TEST_CASE("Formatted") {
    CHECK(format::make_string(S{}) == "hello");
}
#ifdef TEST_VECTOR
TEST_CASE("vector<T>") {
    std::vector<S> vec(2);
    CHECK(format::make_string(vec) == "{hello, hello}");
}
#endif
}
#endif

#ifdef TEST_FORMAT_MEMBER_SFINAE
TEST_SUITE("bad .format() member") {
TEST_CASE("Non-const qualified") {
    struct {
        std::string format() { return "hello"; }
    } s;
    CHECK(!is_formattable(s));
}
TEST_CASE("Rvalue-ref-qualified") {
    struct {
        std::string format() && { return "hello"; }
    } s;
    CHECK(!is_formattable(s));
}
TEST_CASE("Returns non-std::string") {
    struct {
        int format() const { return 10; }
    } s;
    CHECK(!is_formattable(s));
}
}
#endif
