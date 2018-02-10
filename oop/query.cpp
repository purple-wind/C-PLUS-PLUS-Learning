/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "query.h"
#include<algorithm>
std::ostream& operator<< ( std::ostream& os,const Query& query )
{
  return os<<query.rep();
}
QueryResult OrQuery::eval ( const TextQuery& text ) const
{
	std::cout<<"run | eval"<<std::endl;
  auto right=rhs.eval ( text ),left=lhs.eval ( text );
  auto ret_lines= std::make_shared<std::set<line_no> > ( left.begin(),left.end() );
  ret_lines->insert ( right.begin(),right.end() );
  return QueryResult ( rep(),ret_lines,left.get_file() );
}

QueryResult AndQuery::eval(const TextQuery& text)const{
	std::cout<<"run & eval"<<std::endl;
	auto left=lhs.eval(text),right=rhs.eval(text);
	auto ret_lines=std::make_shared<std::set<line_no> >();
	std::set_intersection(left.begin(),left.end(),right.begin(),right.end(),std::inserter(*ret_lines,ret_lines->begin()));
	return QueryResult(rep(),ret_lines,left.get_file());
}

QueryResult NotQuery::eval(const TextQuery& text)const{
	std::cout<<"run ~ eval"<<std::endl;
	auto result=query.eval(text);
	auto ret_lines=std::make_shared<std::set<line_no>>();
	auto beg=result.begin(),end=result.end();
	auto sz=result.get_file()->size();
	for(size_t n=0;n!=sz;++n)
	{
		if(beg==end || *beg!=n)
		{
			ret_lines->insert(n);
		}
	    else if(beg!=end)
			++beg;
	}
	return QueryResult(rep(),ret_lines,result.get_file());
}
TextQuery::TextQuery ( std::ifstream& is ) :file ( new std::vector<std::string> )
{
  std::string text;
  while ( std::getline ( is,text ) )
    {
      file->push_back ( text );
      int n=file->size()-1;
      std::istringstream line ( text );
      std::string word;
      while ( line>>word )
        {
          auto& lines=wm[word];
          if ( !lines )
            {
              lines.reset ( new std::set<line_no> );
            }
          lines->insert ( n );
        };
    };
}
QueryResult TextQuery::query ( const std::__cxx11::string& sought) const
{
  static std::shared_ptr<std::set<line_no>>nodata ( new std::set<line_no> );
  auto loc=wm.find ( sought );
  if ( loc==wm.end() )
    {
      return QueryResult ( sought,nodata,file );
    }
  else
    {
      return QueryResult ( sought,loc->second,file );
    }
}
