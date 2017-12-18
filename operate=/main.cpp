#include<unordered_map>
struct A
{
 int a;
 std::unordered_map<std::string, std::string>env;
};
int main()
{
 std::unordered_map<std::string, std::string>env;
 env.insert({"a","b"});
  env.insert({"c","d"});
   env.insert({"e","f"});
   A value;
   value.env=env;
   return 0;
}
