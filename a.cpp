
template < typename T >
class Two {
  public:
    T two[2];
};
  
template < typename T >
class Indirect {
  public:
  using Tuple = Two<T>;
  Tuple tuple;
  
  void set(Tuple& t) {
    tuple = t;
  }
};

int main() {
  Indirect<int> i;
  Two<int> t = {.two = {1,1} };
  i.set(t);
  return 1;
}
