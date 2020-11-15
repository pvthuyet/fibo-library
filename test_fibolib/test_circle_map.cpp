#include "pch.h"

import Fibo.ConcurrentCircleMap;
constexpr int mapSz = 100;

using KeyType = std::string;
struct DataType 
{
	DataType() = default;
	explicit DataType(int v) : value_{ v } {}
	int value_{};
	constexpr auto operator<=>(DataType const&) const noexcept = default;
};

using TestCirMap = fibo::Con::CircleMap<KeyType, DataType, mapSz>;

TestCirMap initMap(int sz = mapSz)
{
	using namespace std::string_literals;
	TestCirMap mp{};
	for (int i = 0; i < sz; ++i) {
		std::string key = "key "s + std::to_string(i);
		DataType v{ i };
		mp[key] = v;
	}
	return mp;
}

TEST(CircleMap, constructor_fix_size)
{
	TestCirMap ciMap;
	TestCirMap ciMap1 = initMap();
	ciMap = ciMap1;
	TestCirMap ciMap3{ std::move(ciMap1) };
	EXPECT_EQ(mapSz, ciMap.size());
}

TEST(CircleMap, insert_item)
{
	DataType v{};
	KeyType key = "key 1";
	TestCirMap ciMap{};
	ciMap[key] = v;
	EXPECT_EQ(v, ciMap[key]);
}

TEST(CircleMap, find_in_empty_circle_map)
{
	TestCirMap ciMap{};
	auto found = ciMap.find("key 1");
	EXPECT_TRUE(not found);
}

TEST(CircleMap, find_available_item)
{
	DataType v{};
	TestCirMap ciMap{};
	ciMap["key 1"] = v;
	auto found = ciMap.find("key 1");
	EXPECT_EQ(v, *found);
}

TEST(CircleMap, find_not_found_item)
{
	TestCirMap ciMap{};
	ciMap["key 1"] = DataType{};
	auto found = ciMap.find("key 2");
	EXPECT_TRUE(not found);
}

TEST(CircleMap, find_if_available_item)
{
	DataType v{};
	TestCirMap ciMap{};
	ciMap["key 1"] = v;
	auto found = ciMap.find_if([&](auto const& k, auto const& val) {
		return val == v;
		});
	EXPECT_EQ(v, *found);
}