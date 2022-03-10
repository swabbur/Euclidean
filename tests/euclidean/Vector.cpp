#include <catch2/catch.hpp>
#include <euclidean/Vector.hpp>

//TEST_CASE("Vector default construction") {
//    Vector<int, 3> vector;
//    REQUIRE(vector[0] == Approx(0));
//    REQUIRE(vector[1] == Approx(0));
//    REQUIRE(vector[2] == Approx(0));
//}

//TEST_CASE("Vector initializer list") {
//    Vector<int, 3> vector = { 1, 2, 3 };
//    REQUIRE(vector[0] == Approx(1.0f));
//    REQUIRE(vector[1] == Approx(2.0f));
//    REQUIRE(vector[2] == Approx(3.0f));
//}

//TEST_CASE("Vector explicit") {
//    Vector<int, 3> vector(1, 2, 3);
//    REQUIRE(vector[0] == Approx(1.0f));
//    REQUIRE(vector[1] == Approx(2.0f));
//    REQUIRE(vector[2] == Approx(3.0f));
//}

//TEST_CASE("Vector composition") {
//    Vector<int, 4> vector(1, Vector<int, 2>(2, 3), 4);
//    REQUIRE(vector[0] == Approx(1.0f));
//    REQUIRE(vector[1] == Approx(2.0f));
//    REQUIRE(vector[2] == Approx(3.0f));
//    REQUIRE(vector[3] == Approx(4.0f));
//}
