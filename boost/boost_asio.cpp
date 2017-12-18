#include<boost/asio.hpp>
#include<boost/thread.hpp>
#include<unistd.h>
#include<stdio.h>

using namespace boost::asio;
void connect_handler ( boost::system::error_code err )
{
  std::cout<<"client connect err "<<err.message() <<std::endl;
}

namespace AsioService
{
typedef boost::asio::io_service IoService;
typedef boost::asio::ip::tcp TCP;
#define PRINT_DEBUG(str) std::cout<<str<<std::endl;
std::string make_daytime_string()
{
  using namespace std;
  time_t now = std::time ( NULL );
  return ctime ( &now );
}

class tcp_connection: public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create ( IoService& io_service )
  {
    return pointer ( new tcp_connection ( io_service ) );
  }

  TCP::socket& socket()
  {
    return socket_;
  }

  void start()
  {
//     std::cout<<"service tcp_connection start"<<std::endl;
    message_ = make_daytime_string();
//    std::cout<<"message_="<<message_<<std::endl;
    boost::asio::async_write (
      socket_,
      boost::asio::buffer ( message_ ),
      boost::bind ( &tcp_connection::handle_write,
                    shared_from_this(),
                    _1,
                    boost::asio::placeholders::bytes_transferred ) );


    boost::asio::async_read(
      socket_,
      boost::asio::buffer(data_,64),
      boost::bind(&tcp_connection::handle_read,
                  shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
  }

private:
  tcp_connection ( IoService& io_service ) : socket_ ( io_service ) {}

  void handle_write ( const boost::system::error_code& err,size_t size )
  {
    PRINT_DEBUG ( "service write data!!!" );
//     std::cout<<"service write size ="<<size<<std::endl;
    
    boost::asio::async_read(
      socket_,
      boost::asio::buffer(data_,64),
                            boost::bind(&tcp_connection::handle_read,
                                        shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
  }
  void handle_read(const boost::system::error_code& err,size_t size)
  {
//     PRINT_DEBUG("service read data!!!");
    uint32_t now_time;
    memcpy(&now_time,data_,4);
    std::cout<<"service read ="<<now_time<<std::endl;
    message_ = make_daytime_string();
    boost::asio::async_write (
      socket_,
      boost::asio::buffer ( message_ ),
                              boost::bind ( &tcp_connection::handle_write,
                                            shared_from_this(),
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred ) );
    
  }
  TCP::socket socket_;
  std::string message_;
  char data_[64];
};

class tcp_server
{
public:
  tcp_server ( IoService& io_service ) : acceptor_ ( io_service, TCP::endpoint (ip::address_v4::from_string("127.0.0.1"), 10000 ) )
  {
    start_accept();
  }
private:
  void start_accept()
  {
    std::cout<<"service start accept"<<std::endl;
    tcp_connection::pointer new_connection = tcp_connection::create ( acceptor_.get_io_service() );
    sock_ptr=new_connection;
    acceptor_.async_accept (
      new_connection->socket(),
      boost::bind ( &tcp_server::handle_accept,
                    this,
                    new_connection,
                    boost::asio::placeholders::error ) );
  }

  void handle_accept ( tcp_connection::pointer new_connection,const boost::system::error_code& error )
  {
    std::cout<<"service handle accpet"<<std::endl;
    start_accept();
    if ( !error )
      {
        new_connection->start();
      }

  }

  TCP::acceptor acceptor_;
  tcp_connection::pointer sock_ptr;
};
}

class tcp_client
{
public:
  tcp_client(io_service& io_ser,ip::tcp::endpoint ep):m_sock(io_ser),m_ep(ep){
    std::cout<<"client tcp_client"<<std::endl;

    m_sock.async_connect(ep,bind(&tcp_client::client_callback,this,boost::asio::placeholders::error));
    write("hello world 1",12);
  }
  void client_callback (const boost::system::error_code& err )
  {
    std::cout<<"run client_callback"<<std::endl;
    write("hello world",11);
  }

  void write(const char* data,size_t len)
  {
    m_sock.async_write_some(buffer(data,len),boost::bind(&tcp_client::write_callback,this,boost::asio::placeholders::error));
  }

  void write_callback(boost::system::error_code err)
  {
    std::cout<<"err code="<<err.value()<<" "<<err.message()<<std::endl;
  }
  void read()
  {
    char data[1024];
    memset(data,0x00,sizeof(data));
    m_sock.async_read_some(buffer(data,sizeof(data)),boost::bind(&tcp_client::read_callback,this,boost::asio::placeholders::error));
  }
  void read_callback(boost::system::error_code err)
  {
    std::cout<<"err code="<<err.value()<<" "<<err.message()<<std::endl;
  }
private:
  ip::tcp::socket m_sock;
  ip::tcp::endpoint m_ep;
};


void write_callback(boost::system::error_code err)
{
  std::cout<<"----client write_callback"<<std::endl;
  std::cout<<"client err code="<<err.value()<<" "<<err.message()<<std::endl;
}

void read_callback( boost::system::error_code err)
{
  std::cout<<"----client read_callback"<<std::endl;
  std::cout<<"client err code="<<err.value()<<" "<<err.message()<<std::endl;
}

int main()
{
  pid_t pid=fork();
  if ( pid<0 )
    {
      std::cout<<"fork fail"<<std::endl;
    }
  else if ( pid==0 )
    {
      sleep(3);
//       io_service service;
//       ip::tcp::endpoint ep(ip::address_v4::from_string("127.0.0.1"),htons(10000));
//       tcp_client client(service,ep);
         try{
            std::cout<<"I`m child process"<<std::endl;
            boost::asio::io_service service;
            boost::asio::ip::tcp::endpoint ep ( boost::asio::ip::address_v4::from_string("127.0.0.1"),10000 );
            boost::asio::ip::tcp::socket sock ( service );
            sock.async_connect( ep,connect_handler );
            int c=0;
            while ( true )
              {
                sleep (1);
                service.run();
                char longdata[64];
                time_t now=time(0);
                memcpy(longdata,&now,4);
                sock.write_some( buffer ( longdata,sizeof ( longdata ) ) );


                char data[64]= {0};
                int b=100;
                sock.async_read_some( buffer ( data,64),boost::bind(read_callback,boost::asio::placeholders::error ));
                std::cout<<"client read="<<data<<std::endl;
                c++;
              };
         }
         catch(boost::system::system_error err)
         {
         std::cout<<"client expection"<<err.what()<<std::endl;
         }

      exit ( -1 );
    }
  else
    {
      try
        {
          AsioService::IoService io_service;
          AsioService::tcp_server server ( io_service );
//           只有io_service类的run()方法运行之后回调对象才会被调用
          io_service.run();
          std::cout<<"service after run"<<std::endl;
        }
      catch ( std::exception& e )
        {
          std::cerr <<"service err="<< e.what() << std::endl;
        }
    }
    return 0;
}






















