#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <Command.hpp>

TEST_CASE("Not a command")
{
	auto cmd = Command::parse("toto");
	CHECK(!cmd.has_value());
}

TEST_CASE("Still not a command and too short")
{
	auto cmd = Command::parse("t");
	CHECK(!cmd.has_value());
}

TEST_CASE("Empty input")
{
	auto cmd = Command::parse("");
	CHECK(!cmd.has_value());
}

TEST_CASE("Only '!'")
{
	auto cmd = Command::parse("!");
	CHECK(!cmd.has_value());
}

TEST_CASE("Command with name only")
{
	auto cmd = Command::parse("!toto");
	REQUIRE(cmd.has_value());
	CHECK(cmd->name == "toto");
	CHECK(cmd->message.empty());
}

TEST_CASE("Command with name only but with a space")
{
	auto cmd = Command::parse("!toto ");
	REQUIRE(cmd.has_value());
	CHECK(cmd->name == "toto");
	CHECK(cmd->message.empty());
}

TEST_CASE("Command with content")
{
	auto cmd = Command::parse("!toto lol");
	REQUIRE(cmd.has_value());
	CHECK(cmd->name == "toto");
	CHECK(cmd->message == "lol");
}

TEST_CASE("Command with a long content")
{
	auto cmd = Command::parse("!toto lol c'est vraiment trop marrant");
	REQUIRE(cmd.has_value());
	CHECK(cmd->name == "toto");
	CHECK(cmd->message == "lol c'est vraiment trop marrant");
}