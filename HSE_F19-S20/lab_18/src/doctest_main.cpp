#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>  // https://github.com/onqtam/doctest/issues/356
#include <string>

using namespace doctest;

struct VerboseConsoleReporter : public ConsoleReporter {
private:
    std::string last_test_suite;
    std::string test_suite_indent;

public:
    using ConsoleReporter::ConsoleReporter;

    void test_case_start(const TestCaseData& in) override {
        ConsoleReporter::test_case_start(in);
        if (last_test_suite != in.m_test_suite) {
            last_test_suite = in.m_test_suite;
            if (!last_test_suite.empty()) {
                s << Color::None << "TEST_SUITE(" << last_test_suite << ")\n";
                test_suite_indent = "    ";
            } else {
                test_suite_indent = "";
            }
        }
        s << Color::None << test_suite_indent << "TEST_CASE(" << in.m_name << ")\n";
        s.flush();
    }

    void subcase_start(const SubcaseSignature& subc) override {
        ConsoleReporter::subcase_start(subc);
        s << Color::None << test_suite_indent << "    SUBCASE(" << subc.m_name << ")\n";
        s.flush();
    }
};

REGISTER_REPORTER("verbose", 1, VerboseConsoleReporter);
