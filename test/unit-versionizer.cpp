#include "catch2/catch.hpp"

#include "versionizer.hpp"

TEST_CASE("versionToString() check", "[vrsionizer]")
{
    auto vizer = versionizer::Versionizer();

    SECTION("type M") {
        vizer.setType("M");

        REQUIRE(vizer.versionToString({0,0,0,0}) == "0");
        REQUIRE(vizer.versionToString({1,2,3,4}) == "1");
        REQUIRE(vizer.versionToString({2,-1,-1,-1}) == "2");

        REQUIRE_THROWS(vizer.versionToString({-1,0,0,0}));
    }

    SECTION("type MM") {
        vizer.setType("MM");

        REQUIRE(vizer.versionToString({0,0,0,0}) == "0.0");
        REQUIRE(vizer.versionToString({1,2,3,4}) == "1.2");

        REQUIRE_THROWS(vizer.versionToString({2,-1,-1,-1}));
        REQUIRE_THROWS(vizer.versionToString({-1,0,0,0}));
    }

    SECTION("type MR") {
        vizer.setType("MR");

        REQUIRE(vizer.versionToString({0,0,0,0}) == "0");
        REQUIRE(vizer.versionToString({1,2,3,4}) == "1-rc4");

        REQUIRE_THROWS(vizer.versionToString({2,-1,-1,-1}));
        REQUIRE_THROWS(vizer.versionToString({-1,0,0,0}));
    }

    SECTION("type MMP") {
        vizer.setType("MMP");

        REQUIRE(vizer.versionToString({0,0,0,0}) == "0.0.0");
        REQUIRE(vizer.versionToString({1,2,3,4}) == "1.2.3");

        REQUIRE_THROWS(vizer.versionToString({2,-1,-1,-1}));
        REQUIRE_THROWS(vizer.versionToString({-1,0,0,0}));
    }

    SECTION("type MMR") {
        vizer.setType("MMR");

        REQUIRE(vizer.versionToString({0,0,0,0}) == "0.0");
        REQUIRE(vizer.versionToString({0,0,0,1}) == "0-rc1");
        REQUIRE(vizer.versionToString({1,2,3,4}) == "1-rc4");

        REQUIRE_THROWS(vizer.versionToString({2,-1,-1,-1}));
        REQUIRE_THROWS(vizer.versionToString({-1,0,0,0}));
    }

    SECTION("type MMPR") {
        vizer.setType("MMPR");

        REQUIRE(vizer.versionToString({0,0,0,0}) == "0.0.0");
        REQUIRE(vizer.versionToString({0,0,0,1}) == "0.0-rc1");
        REQUIRE(vizer.versionToString({1,2,3,4}) == "1.2-rc4");

        REQUIRE_THROWS(vizer.versionToString({2,-1,-1,-1}));
        REQUIRE_THROWS(vizer.versionToString({-1,0,0,0}));
    }
}
