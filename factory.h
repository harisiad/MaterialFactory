#ifndef MATERIALFACTORY_FACTORY_H
#define MATERIALFACTORY_FACTORY_H

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <functional>


enum MaterialType
{
    NONE = -1,
    SWORD = 0,
    AXE = 1,
    SHIELD = 2,
};

class MaterialPayloader
{
public:
    std::string *name() { return name_; }

    std::string description() { return description_; }

    MaterialType type() { return type_; }

    MaterialPayloader *setName(std::string *name)
    {
        name_ = name;
        return this;
    }

    MaterialPayloader *setDescription(std::string description)
    {
        description_ = std::move(description);
        return this;
    }

    MaterialPayloader *setType(MaterialType type)
    {
        type_ = type;
        return this;
    }

    MaterialPayloader() : name_(new std::string()),
                          type_(MaterialType::NONE) {}

    ~MaterialPayloader() { delete name_; }

private:
    std::string *name_;
    MaterialType type_;
    std::string description_;
};

class Material
{
public:
    explicit Material(MaterialPayloader *);

    Material(const Material &);

    static void instances()
    {
        std::cout << "The number of Material instances are: " << numberOfInstances_ << std::endl;
    }

    virtual ~Material() { delete name_; };

    std::string name() const { return *name_; }

    std::string description() const { return description_; }

    MaterialType getType() const { return type_; }

    void setName(std::string *name) { name_ = name; }

    void setDescription(std::string description) { description_ = std::move(description); }

    void setType(MaterialType type) { type_ = type; }

    static long getInstances() { return numberOfInstances_; }

    static inline void increaseInstances() { numberOfInstances_++; }

    virtual void setMaterial() {};

private:
    std::string *name_;
    MaterialType type_;
    std::string description_;
    static long numberOfInstances_;
};

class Sword : public Material
{
public:
    explicit Sword(MaterialPayloader *);

    Sword &operator=(const Sword &);

    void setMaterial() override;
};

class Axe : public Material
{
public:
    explicit Axe(MaterialPayloader *);

    void setMaterial() override;
};

class Shield : public Material
{
public:
    explicit Shield(MaterialPayloader *);

    void setMaterial() override;
};

class MaterialFactory
{
public:
    explicit MaterialFactory(MaterialPayloader *payloader)
    {
        materialMap.insert(std::make_pair(MaterialType::SWORD, new Sword(payloader)));
        materialMap.insert(std::make_pair(MaterialType::AXE, new Axe(payloader)));
        materialMap.insert(std::make_pair(MaterialType::SHIELD, new Shield(payloader)));
    }

    Material *generateMaterial(MaterialType type)
    {
        auto material = materialMap[type];
        material->setMaterial();

        return new Material(*material);
    }

private:
    std::map<MaterialType, Material *> materialMap;
};

#endif //MATERIALFACTORY_FACTORY_H
