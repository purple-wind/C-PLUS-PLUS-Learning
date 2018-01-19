#include<boost/asio.hpp>
#include<boost/thread.hpp>
#include<unistd.h>
#include<stdio.h>


void connect_handler(boost::system::system_coder err)
{
  std::cout<<"client connect err"<<err.message()<<std::endl;
}
void client_session ( boost::shared_ptr<boost::asio::ip::tcp::socket> sock )
{
  std::cout<<"run client session"<<std::endl;
  while ( true )
    {
      char data[512];
      size_t len=sock->read_some ( buffer ( data ) );
//         std::cout<<"service read="<<data<<std::endl;
      if ( len>0 )
        {
          write ( *sock,buffer ( "1234",4 ) );
        }
    };
}


int main()
{

  pid_t pid=fork();
  if ( pid<0 )
    {
      std::cout<<"fork fail"<<std::endl;
      exit ( -1 );
    }
  else if ( pid==0 )
    {
      sleep ( 3 );
      std::cout<<"I`m child process"<<std::endl;
      boost::asio::io_service service;
      boost::asio::ip::tcp::endpoint ep ( boost::asio::ip::address_v4::from_string("127.0.0.1"),10000 );
      boost::asio::ip::tcp::socket sock ( service );
      sock.async_connect( ep,connect_handler );
      int c=0;
      while ( true )
        {
          sleep ( 1 );
          service.run();
          char longdata[65535];
          if ( c%2==0 )
            memset ( longdata,0x22,sizeof ( longdata ) );
          else
            memset ( longdata,0x11,sizeof ( longdata ) );

          sock.write_some ( buffer ( longdata,sizeof ( longdata ) ) );
          char data[16]= {0};
          sock.read_some ( buffer ( data,4 ) );
          std::cout<<"client read="<<data<<std::endl;
          fflush ( stdout );
          c++;
        };
      exit ( -1 );
    }
  else
    {
      boost::asio::io_service service;
      boost::asio::ip::tcp::endpoint ep ( boost::asio::ip::tcp::v4(),10000 );
      boost::asio::ip::tcp::acceptor acc ( service,ep );
      while ( true )
        {
          boost::shared_ptr<boost::asio::ip::tcp::socket> sock ( new boost::asio::ip::tcp::socket ( service ) );
          acc.accept ( *sock );
          boost::thread ( bind ( client_session,sock ) );
        };
    }
  return 0;
}
