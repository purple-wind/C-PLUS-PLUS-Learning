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

#ifndef QUERY_H
#define QUERY_H
#include<string>
#include<memory>
#include<iostream>
#include<fstream>
#include<sstream>
#include<set>
#include<map>
#include<vector>
class QueryResult{
	friend std::ostream& print(std::ostream&,const QueryResult&);
    using line_no=std::vector<std::string>::size_type;
public:
	QueryResult(std::string s,std::shared_ptr<std::set<line_no>>p,std::shared_ptr<std::vector<std::string>>f):sought(s),lines(p),file(f){}
	std::set<line_no>::iterator begin(){
		return lines->begin();
	}
	std::set<line_no>::iterator end(){
		return lines->end();
	}
	std::shared_ptr<std::vector<std::string>> get_file(){
		return file;
	}
private:
	std::string sought;
	std::shared_ptr<std::set<line_no>>lines;//出现的行号
	std::shared_ptr<std::vector<std::string> >file;//输入文件
};
inline std::ostream& print(std::ostream& os,const QueryResult& qr)
{
	
}

class TextQuery{
public:
    using line_no=std::vector<std::string>::size_type;
    TextQuery ( std::ifstream& is );
    QueryResult query ( const std::string& ) const;
private:
    std::shared_ptr<std::vector<std::string>>file;
    std::map<std::string,std::shared_ptr<std::set<line_no>>>wm;
};






class Query_base
{
    friend class Query;
protected:
    using line_no=TextQuery::line_no;
    virtual ~Query_base() =default;
private:
    virtual QueryResult eval ( const TextQuery& ) const=0;
    virtual std::string rep() const=0;
};




class WordQuery: public Query_base
{
    friend class Query;
    WordQuery ( const std::string& s ) :query_word ( s ) {

    }

    QueryResult eval ( const TextQuery& t ) const {
        return t.query ( query_word );
    }

    std::string rep() const {
        return query_word;
    }

    std::string query_word;//要查找的单词
};


// 接口类
class Query
{
    friend Query operator~ ( const Query & );
    friend Query operator| ( const Query&,const Query& );
    friend Query operator& ( const Query&,const Query& );
public:
    Query ( const std::string& s ) : q( new WordQuery ( s ) ) {}

    QueryResult eval ( const TextQuery&t ) const {
        return q->eval ( t );
    }

    std::string rep() const {
        return q->rep();
    }

private:
    Query ( std::shared_ptr<Query_base>query ) :q ( query ) {}
    std::shared_ptr<Query_base>q;
};





class NotQuery: public Query_base
{
    friend Query operator~ ( const Query& );
    NotQuery ( const Query& q ) :query ( q ) {}
    std::string rep() const {
        return "~("+query.rep() +")";
    }
    QueryResult eval ( const TextQuery& ) const;
    Query query;
};
inline Query operator~ ( const Query& operand )
{
    return std::shared_ptr<Query_base> (new NotQuery(operand));
}






class BinaryQuery: public Query_base{
protected:
	BinaryQuery ( const Query& l,const Query& r,std::string s ): lhs ( l ),rhs ( r ),opSym ( s ) {}
	
    std::string rep() const {
        return "("+lhs.rep() +" "+opSym+ "" + rhs.rep() +")";
    }
    Query lhs,rhs;
    std::string opSym;
};

class AndQuery:public BinaryQuery{
    friend Query operator& ( const Query&,const Query& );
    AndQuery ( const Query& left,const Query& right ) :BinaryQuery(left,right,"&") {}
    QueryResult eval ( const TextQuery& ) const;
};

inline Query operator& ( const Query&lhs,const Query& rhs )
{
    return std::shared_ptr<Query_base> ( new AndQuery ( lhs,rhs ) );
}

class OrQuery: public BinaryQuery
{
    friend Query operator| ( const Query&,const Query& );
    OrQuery ( const Query&left,const Query& right ):BinaryQuery (left,right,"|"){}
    QueryResult eval ( const TextQuery& ) const;
};

inline Query operator| ( const Query& lhs,const Query& rhs )
{
    return std::shared_ptr<Query_base> ( new OrQuery ( lhs,rhs ) );
}



#endif // QUERY_H















