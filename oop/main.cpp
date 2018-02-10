#include"quote.h"
#include"query.h"
int main()
{
  Quote item;
  Bulk_quote bulk;
  Quote* base_p=&bulk;
  base_p=&item;
  Quote& reference_r=bulk;
  
  Bulk_quote2 bq2;
  bq2.clobber2(item);
  base_p=&bq2;
  base_p->isbn();
  bq2.my_number();
   /*由于成员的可见性是由静态类型决定的，base_p的静态类型是Quote，所以派生类中的新成
	* 员对Quote来说是不可见的。即使base_p指向的是Bulk_quote2
	*/
//   base_p->my_number();

  Query q1("hello"),q2("world");
  std::ifstream ifs("./test_infile.txt",std::ios::in);
  TextQuery tq(ifs);
  auto it=~q1;
  it.eval(tq);
  it=q1&q2;
  it.eval(tq);
  it=q1|q2;
  it.eval(tq);
  return 0;
}