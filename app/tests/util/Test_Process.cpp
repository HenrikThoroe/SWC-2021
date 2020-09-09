#include "catch.hpp"
#include "Process.hpp"

using namespace Util;

TEST_CASE("Process Test", "[util]") {
    auto pro = Process();

    REQUIRE(pro.rss() > 0);
    REQUIRE(pro.virtualMemory() > 0);
}