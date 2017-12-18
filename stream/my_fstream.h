#ifndef __MY_FSTREAM_H__
#define __MY_FSTREAM_H__
#include<iostream>
class Fstream{
public:
  void rw_binary(const char*);
  void test_getline(void);
  static void c_file();
};

#endif