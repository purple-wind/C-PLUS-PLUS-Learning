#include<boost/algorithm/string.hpp>
#include<boost/regex/config.hpp>
#include<boost/regex/v4/match_flags.hpp>
#include<boost/regex.hpp>
#include<string>
#include<iostream>
using namespace  std;
int main()
{
    boost::regex idcard("[^0-9X]");
    string instr = "42010019000101123X";
    std::string result = boost::regex_replace(instr , idcard ,"", boost::match_default | boost::format_all);
    std::cout<<"result="<<result<<std::endl;

    //    string s1 = "(<)|(>)|(&)";
    //    string s2 = "(?1&lt;)(?2&gt;)(?3&amp;)";
    //    boost::regex reg( s1 );
    //    string s = boost::regex_replace( string("cout << a&b << endl;"), reg, "", boost::match_default | boost::format_all);
    //    cout << "HTML:"<< s << endl;
}
