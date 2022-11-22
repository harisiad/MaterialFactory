#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <ctime>
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

class Sword : public Material
{
public:
    explicit Sword(MaterialPayloader *);

    Sword &operator=(const Sword&);

    void setMaterial() override;
};

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

class Axe : public Material
{
public:
    explicit Axe(MaterialPayloader *);

    void setMaterial() override;
};

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

class Shield : public Material
{
public:
    explicit Shield(MaterialPayloader *);

    void setMaterial() override;
};

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
    std::map<MaterialType, Material*> materialMap;
};

int main()
{
    auto seed = static_cast<unsigned int>(std::time(nullptr));
    std::vector<Material *> materials;
    MaterialPayloader *payloader = (new MaterialPayloader())
            ->setName(new std::string("Sword"))
            ->setDescription("This is an aweeesome sword");
    MaterialFactory factory(payloader);
    int rand = -1;

    std::srand(seed);
    materials.reserve(100);
    for (int i = 0; i < 100; i++) {
        rand = (std::rand() % 10) / 3;
        if (rand > 2) rand = 2;
        materials.push_back(factory.generateMaterial(MaterialType(rand)));
    }

    int y = 0;
    for (Material *t: materials) {
        std::cout << y << ":" << t->name() << " " << t->description() << " type : " << t->getType() << " address: "
                  << &materials[y] << std::endl;
        y++;
    }

    materials.front()->instances();

    return 0;
}
