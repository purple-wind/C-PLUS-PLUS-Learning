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
 return bookNo;
}

double Quote::net_price(size_t price)const
{
  
}



//Bulk_quote
Bulk_quote::Bulk_quote(const std::string& book,double p,std::size_t qty,double disc):Quote(book,p),min_qty(qty),discount(disc){
  
}
double Bulk_quote::net_price(std::size_t cnt)const
{
  if(cnt>=min_qty)
    return cnt*(1-discount)*price;
  else
    return cnt*price;
}
