/*
 * Copyright 2017 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#ifndef ENUM_UNION_H
#define ENUM_UNION_H
#include<string>
class enum_union
{
public:
enum_union();
enum_union(std::string* arg_str);
enum_union(const enum_union& other);
~enum_union();
enum_union& operator=(const enum_union& other);
bool operator==(const enum_union& other) const;
void no_scopes_enum();
void scopes_enum();
void my_union();
std::string* get_str();
private:
  enum color{red,blue,yellow};
  enum class Color{red,blue,yellow};
  union digital_type{
	  short shorter;
	  int inter;
	  long longer;
  };
public:
  std::string* str;
};

#endif // ENUM_UNION_H
