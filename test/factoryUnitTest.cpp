#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include "../factory.h"

TEST_CASE("test factory") {
    MaterialFactory factory((new MaterialPayloader())
    ->setName(new std::string("DUMMY MATERIAL"))
    ->setDescription("DUMMY DESCRIPTION")
    );

    CHECK(dynamic_cast<const Material*>(factory.generateMaterial(MaterialType(MaterialType::SWORD))) != nullptr);
    CHECK(dynamic_cast<const Material*>(factory.generateMaterial(MaterialType(MaterialType::AXE))) != nullptr);
    CHECK(dynamic_cast<const Material*>(factory.generateMaterial(MaterialType(MaterialType::SHIELD))) != nullptr);
}