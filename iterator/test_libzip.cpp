#include<zip.h>
#include<iostream>
#include<string>
#include<unistd.h>
#include<string.h>
using namespace std;
int ZipFile(const string& src_fpath, const string& dst_fpath, const string& passwd)
{
    if(access(src_fpath.c_str(), F_OK))
        return -1;

    int ierr = 0;
    struct zip *zipfile = nullptr;
    struct zip_source *srcfile = nullptr;
    zipfile = zip_open(dst_fpath.c_str(), ZIP_CREATE|ZIP_TRUNCATE, &ierr);
    if(!zipfile)
    {
        return ierr;
    }
    srcfile = zip_source_file(zipfile, src_fpath.c_str(), 0, -1);
    if(srcfile == nullptr)
    {
        zip_close(zipfile);
        return ierr;
    }
    zip_file_add(zipfile, src_fpath.c_str(), srcfile, ZIP_FL_OVERWRITE);


    srcfile = zip_source_file(zipfile, "2.txt", 0, -1);
    if(srcfile == nullptr)
    {
        zip_close(zipfile);
        return ierr;
    }
    zip_file_add(zipfile, "2.txt", srcfile, ZIP_FL_OVERWRITE);


    if(!passwd.empty())
        zip_file_set_encryption(zipfile, 0, ZIP_EM_AES_128, passwd.c_str());

    zip_close(zipfile);
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        std::cout<<"args error"<<std::endl;
        return -1;
    }
    for(int i = 0; i< argc; i++)
    {
        std::cout<<"arg["<<i<<"]="<<argv[i]<<std::endl;
    }
    ZipFile(argv[1], argv[2], "");
}
