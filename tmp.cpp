#include <memory>
#include <string>
#include <map>
#include <iostream>

class animal
{
public:
  virtual ~animal() {};
  virtual void make_sound() const = 0;
};

class dog : public animal
{
public:
  void make_sound() const { std::cout << "bark" << std::endl; }
};
class bird : public animal
{
public:
  void make_sound() const { std::cout << "chirp" << std::endl; }
};

int main()
{
  std::map<std::string, std::unique_ptr<animal>> m;
  m.insert(std::make_pair("stupid_dog_name", new dog));
  m.insert(std::make_pair("stupid_bird_name", new bird));
  m["stupid_dog_name"]->make_sound();
  return 0;
}