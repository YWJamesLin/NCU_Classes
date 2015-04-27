#include <iostream>

using namespace std;

template<typename T>
class Vector
{
  private:
    T* inst;
    int size;

  public:
    Vector()
    {
      inst = NULL;
      size = 0;
    }
    Vector(const T& begin, const T& end)
    {

    }
};

int main()
{
  return 0;
}
