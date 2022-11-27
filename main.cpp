#include <ctime>

#include "factory.h"

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
