#include "factory.h"

long Material::numberOfInstances_ = 0;

Material::Material(MaterialPayloader *payloader)
        : name_(payloader->name()),
          type_(payloader->type()),
          description_(payloader->description())
{
    std::cout << "Material(MaterialPayloader *payloader) executed\n";
}

Material::Material(const Material &material)
{
    std::cout << "Material(const Material &material) executed\n";
    name_ = material.name_;
    description_ = material.description_;
    type_ = material.type_;

    numberOfInstances_++;
}


Sword::Sword(MaterialPayloader *payloader)
        : Material(payloader->setType(MaterialType::SWORD))
{
    std::cout << "Sword(MaterialPayloader *payloader) executed\n";
}

void Sword::setMaterial()
{
    setName(new std::string("Sword " + std::to_string(Sword::getInstances())));
    setDescription("Aweeesome Sword number: " + std::to_string(Sword::getInstances()));
}

Sword &Sword::operator=(const Sword &rhs)
{
    std::cout << "Sword &operator=(const Sword &rhs) executes\n";
    if (this == &rhs) {
        return *this;
    }

    setName(new std::string(rhs.name()));
    setDescription(rhs.description());
    setType(rhs.getType());

    return *this;
}

Axe::Axe(MaterialPayloader *payloader)
        : Material(payloader->setType(MaterialType::AXE))
{
    std::cout << "Axe(MaterialPayloader *payloader) executed\n";
}

void Axe::setMaterial()
{
    setName(new std::string("Axe " + std::to_string(Axe::getInstances())));
    setDescription("Aweeesome Axe number: " + std::to_string(Axe::getInstances()));
}

Shield::Shield(MaterialPayloader *payloader)
        : Material(payloader->setType(MaterialType::SHIELD))
{
    std::cout << "Shield(MaterialPayloader *payloader) executed\n";
}

void Shield::setMaterial()
{
    setName(new std::string("Shield " + std::to_string(Shield::getInstances())));
    setDescription("Aweeesome Shield number: " + std::to_string(Shield::getInstances()));
}
