#include<fstream>
#include<iostream>
#include<unistd.h>
#include<string>
#include<string.h>
#include"my_fstream.h"
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <sys/types.h>
// 读写二进制文件需要用read/write根据字节数读写
void Fstream::rw_binary(const char* filename)
{
    std::ofstream o_stream(filename,std::ios::binary|std::ios::app);
    for(int i=0; i<10; i++)
        o_stream.write((char*)&i,4);
	std::ifstream in_stream(filename,std::ios::binary|std::ios::app);
	o_stream.close();//一定要关闭才能再开始读，否则读不到数据,只有文件关闭了读写才正真生效到文件中
	int a=1000;
	for(int i=0;i<10;i++)
	{
		in_stream.read((char*)&a,4);
		std::cout<<a<<" ";
	}
	std::cout<<std::endl;
}

void Fstream::test_getline(void)
{
	std::cout<<"run tes_getline"<<std::endl;
 std::ifstream in_stream("./test.fin",std::ios::in);
 if(in_stream.bad())
	 std::cout<<"test bad"<<std::endl;

 if(in_stream.good())
 {
	 std::string buf;
	 while(getline(in_stream,buf))
	 {
	  std::cout<<buf<<std::endl;
	 };
	 if(in_stream.eof())
		 std::cout<<"is eof"<<std::endl;
 }
}

//随机流访问
void Fstream::c_file()
{
  
  std::string config_file="/home/ubuntu/123.txt";
  std::string temp_file="/home/ubuntu/temp.txt";
 std::fstream fs(config_file);
 if(!fs)
 {
   std::cout<<"fs bad"<<std::endl;
   return;
 }
 
 std::fstream temp_fs;
 temp_fs.open(temp_file,std::ios::out);
 if(!temp_fs)
 {
   std::cout<<"temp fs bad"<<std::endl;
 }
 
 std::string line;
 std::fstream::pos_type current_pos=fs.tellg();
while(std::getline(fs,line))
 {

   if(line.find("BOOTPROTO")!=std::string::npos)
   {
     size_t src_line_len=line.length();
     std::string new_line;
     std::string::size_type line_pos=line.find("=");
     if(line_pos!=std::string::npos)
     {
       line.replace(line_pos+1,src_line_len-line_pos-1,"static");
     }
   }
   line+="\n";
   temp_fs.write(line.c_str(),line.length());
 };
 
 fs.close();
 temp_fs.close();
 
 std::string cmd="cp ";
 cmd+=temp_file;
 cmd+=" ";
 cmd+=config_file;
 cmd+=" ";
 std::cout<<"cmd="<<cmd<<std::endl;
 system(cmd.c_str());
}













