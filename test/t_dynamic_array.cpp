#include "dynamic_array.hpp"

#include "catch.hpp"

TEST_CASE("Throw std::bad_alloc for too large memory request in dynamic_array()") {
  REQUIRE_NOTHROW(ds::impl::dynamic_array<long>(10));
  REQUIRE_THROWS_AS(ds::impl::dynamic_array<long>(100000000000000ul), std::bad_alloc);
}

// Empty dynamic_array tests
TEST_CASE("dynamic_arrays can be default constructed", "[dynamic_array]") {
  auto arr = ds::impl::dynamic_array<long>();

  SECTION("Default constructed arrays must be empty with no capacity") {
    REQUIRE(arr.size() == 0);
    REQUIRE(arr.capacity() == 0);
    REQUIRE(arr.data() == nullptr);
  }

  SECTION("Max capacity must be fixed") {
    auto arr2 = ds::impl::dynamic_array<int>();
    REQUIRE(arr.max_size() == std::numeric_limits<std::size_t>::max() / sizeof(long));
    REQUIRE(arr2.max_size() == std::numeric_limits<std::size_t>::max() / sizeof(int));
  }

  SECTION("More capacity may be reserved") {
    arr.reserve(128);
    REQUIRE(arr.size() == 0);
    REQUIRE(arr.capacity() == 128);
    REQUIRE(arr.data() != nullptr);
    arr.reserve(128);
    REQUIRE(arr.capacity() == 128);
  }

  // set the array to reserve 128 elements
  arr.reserve(128);

  SECTION("If less capacity is reserved, do nothing") {
    arr.reserve(16);
    REQUIRE(arr.size() == 0);
    REQUIRE(arr.capacity() == 128);
    REQUIRE(arr.data() != nullptr);
  }

  SECTION("If too much memory is requested, throw an exception") {
    REQUIRE_THROWS_AS(arr.reserve(std::numeric_limits<std::size_t>::max()), std::length_error);
    // These should not change
    REQUIRE(arr.size() == 0);
    REQUIRE(arr.capacity() == 128);
    REQUIRE(arr.data() != nullptr);
    REQUIRE_THROWS_AS(arr.reserve(10000000000000ul), std::bad_alloc);
    // These should not change
    REQUIRE(arr.size() == 0);
    REQUIRE(arr.capacity() == 128);
    REQUIRE(arr.data() != nullptr);
  }

  SECTION("It is possible to shrink the allocation to fit the data") {
    arr.shrink_to_fit();
    REQUIRE(arr.size() == 0);
    REQUIRE(arr.capacity() == 0);
    REQUIRE(arr.data() == nullptr);
  }

  arr.shrink_to_fit();

  SECTION("Shrinking to fit when the buffer fits perfectly does nothing") {
    arr.shrink_to_fit();
    REQUIRE(arr.size() == 0);
    REQUIRE(arr.capacity() == 0);
    REQUIRE(arr.data() == nullptr);
  }
}
