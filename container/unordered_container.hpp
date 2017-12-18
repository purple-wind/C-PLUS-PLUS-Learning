#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include<functional>
//给无序关联容器自定义hash函数、比较函数，有一下4中方法
using namespace std;
#define  RECORD_C_FUNCTION

struct Record
{
  string name;
  int val;
};


//方法一:定义hash和比较的函数对象
#ifdef RECORD_FUNCTION_OBJECT

struct RecordHash
{
  size_t operator() ( const Record& rhs ) const
  {
    return hash<string>() ( rhs.name ) ^ hash<int>() ( rhs.val );
  }
};
struct RecordCmp
{
  bool operator() ( const Record& lhs, const Record& rhs ) const
  {
    return lhs.name == rhs.name && lhs.val == rhs.val;
  }
};
unordered_set<Record, RecordHash, RecordCmp> records =
{
  { "b", 100 }, { "a", 80 }, { "cc", 70 }, { "d", 60 }, { "d", 60 }
};
#endif//RECORD_FUNCTION_OBJECT

// 方法二:特例化hash和equal_to类
#ifdef RECORD_NAMESPACE
namespace std
{
template<> struct hash<Record>
{
  size_t operator() ( const Record& rhs ) const
  {
    return hash<string>() ( rhs.name ) ^ hash<int>() ( rhs.val );
  }
};

template<> struct equal_to < Record >
{
  bool operator() ( const Record& lhs, const Record& rhs ) const
  {
    return lhs.name == rhs.name && lhs.val == rhs.val;
  }
};
}
unordered_set<Record> records = {{ "b", 100 }, { "a", 80 }, { "cc", 70 }, { "d", 60 }, { "d", 60 }};
#endif //RECORD_NAMESPACE


//方法三:使用lambd表达式
#ifdef RECORD_LAMBDA
//直接使用auto RecordHash不能编译通过，vs2013
auto &RecordHash = [] ( const Record& rhs )
{
  return hash<string>() ( rhs.name ) ^ hash<int>() ( rhs.val );
};
auto &RecordCmp = [] ( const Record& lhs, const Record& rhs )
{
  return lhs.name == rhs.name && lhs.val == rhs.val;
};
unordered_set<Record, decltype ( RecordHash ), decltype ( RecordCmp ) > records =
{
  10,
  RecordHash, RecordCmp
};
struct RunBeforeMain
{
  RunBeforeMain()
  {
    records.insert ( { "a", 100 } );
  }
};
static RunBeforeMain dummyObject;
#endif//RECORD_LAMBDA


//方法四：直接定义普通C函数，然后实例化模板
#ifdef RECORD_C_FUNCTION
size_t RecordHash ( const Record& rhs )
{
  return hash<string>() ( rhs.name ) ^ hash<int>() ( rhs.val );
}
bool RecordCmp ( const Record& lhs, const Record& rhs )
{
  return lhs.name == rhs.name && lhs.val == rhs.val;
}

void used1()
{
  unordered_set<Record, decltype ( &RecordHash ), decltype ( &RecordCmp ) >records ( 10,RecordHash, RecordCmp );
  std::cout<<"used1 max bucket="<<records.max_bucket_count()<<std::endl;
  std::cout<<"used1 used bucket="<<records.bucket_count()<<std::endl;
  records.insert ( { "a", 100 } );
  records.insert ( { "b", 101 } );
  for ( auto i : records )
    {
      std::cout << "{" << i.name << "," << i.val << "}" << std::endl;
    }
}
void used2(){
  std::unordered_set<Record,decltype(RecordHash)*,decltype(RecordCmp)*> records(10,RecordHash,RecordCmp);
  records.insert ( { "a", 100 } );
  records.insert ( { "b", 101 } );
  for ( auto i : records )
  {
    std::cout << "{" << i.name << "," << i.val << "}" << std::endl;
  }
}

int ha(int arg){
  return arg%2;
}

void used3()
{
  std::unordered_set<int,decltype(ha)*>records(1,ha);
  records.insert(2);
  records.insert(4);
  std::cout<<"bucket max="<<records.max_bucket_count()<<std::endl;
  std::cout<<"used bucket="<<records.bucket_count()<<std::endl;
  std::cout<<"0 bucket count="<<records.bucket_size(0)<<std::endl;
  std::cout<<"2 in bucket="<<records.bucket(2)<<std::endl;
  std::cout<<"4 in bucket="<<records.bucket(4)<<std::endl;
  for ( auto i : records )
  {
    std::cout << "{" << i<<"}" << std::endl;
  }
}

#endif //RECORD_C_FUNCTION















