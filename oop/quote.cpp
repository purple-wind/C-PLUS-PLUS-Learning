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

#include "quote.h"
#include <iostream>

// Quote

Quote::Quote ( const Quote& other )
{

}

Quote& Quote::operator= ( const Quote& other )
{

}

bool Quote::operator== ( const Quote& other ) const
{

}

std::string Quote::isbn() const
{
	std::cout<<"isbn="<<bookNo<<std::endl;
 return bookNo;
}

double Quote::net_price(size_t price)const
{
  
}

//Bulk_quote
Bulk_quote::Bulk_quote(const std::string& book,double p,std::size_t qty,double disc):Quote(book,p),min_qty(qty),discount(disc)
{
  
}

double Bulk_quote::net_price(std::size_t cnt)const
{
  if(cnt>=min_qty)
    return cnt*(1-discount)*price;
  else
    return cnt*price;
}

double Bulk_quote::print_total(std::ostream&os,const Quote& item,size_t n)
{
 double ret=item.net_price(n);
 os<<"ISBN:"<<item.isbn()<<" # sold:"<<n<<" total due:"<<ret<<std::endl;
 return ret;
}


double Bulk_quote1::net_price ( std::size_t ) const
{

}


void clobber(Bulk_quote2& s)
{
	std::cout<<s.price<<std::endl;
}

void clobber(Quote& q)
{
// 	std::cout<<q.price<<std::endl;
}

void Bulk_quote2::clobber2(Quote& q)
{
	std::cout<<"price="<<price<<std::endl;
// 	std::cout<<"price quote="<<q.price<<std::endl;
}



double Basket::total_receipt ( std::ostream& os ) const
{
	double sum=0.0;
	for ( auto iter=items.cbegin(); iter!=items.cend(); iter=items.upper_bound ( *iter ) )
	{
		sum+=print_total ( os,**iter,items.count ( *iter ) );
	}
}
void Basket::add_item ( const std::shared_ptr< Quote >& sale )
{
	items.insert ( sale );
}
bool Basket::compare ( const std::shared_ptr< Quote >& lhs, const std::shared_ptr< Quote >& rhs )
{
	return lhs->isbn() < rhs->isbn();
}


double print_total ( std::ostream& os, const Quote& item, size_t n )
{
  double ret=item.net_price ( n );
  os<<"ISBN:"<<item.isbn() <<" # sold:"<<n<<" total due:"<<ret<<std::endl;
  return ret;
}


