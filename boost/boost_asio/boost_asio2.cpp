#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include<boost/thread.hpp>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
using namespace boost;
using namespace boost::asio;
using ip::tcp;
using namespace std;
using boost::system::error_code;
void write_callback ( boost::system::error_code err )
{
  std::cout<<"err code="<<err.value() <<" "<<err.message() <<std::endl;
}

void read_callback ( boost::system::error_code err )
{
  std::cout<<"err code="<<err.value() <<" "<<err.message() <<std::endl;
}
void connect_handler ( boost::system::error_code err )
{
  std::cout<<"client connect err"<<err.message() <<std::endl;
}
class Connection:public boost::enable_shared_from_this<Connection>
{
public:
  Connection ( io_service& s ) : socket ( s )
  {
    std::cout<<"Connection"<<std::endl;
  }

  ~Connection()
  {
    socket.close();
    cout << "~Connection" << endl;
  }

  void StartWork()
  {
    time_t now = std::time ( NULL );
    boost::asio::async_read(socket,
                             boost::asio::buffer(read_buffer),
                             boost::bind(&Connection::AfterReadChar,
                                         shared_from_this(),
                                         _1));
    
    boost::asio::async_write(socket,
                               boost::asio::buffer(std::string(ctime(&now))),
                               boost::bind(&Connection::AfterWriteChar,
                                           shared_from_this(),
                                           _1));

  }
    void AfterReadChar(const boost::system::error_code& err)
  {
    time_t now = std::time ( NULL );
    boost::asio::async_write(socket,
                             boost::asio::buffer(std::string(ctime(&now))),
                             boost::bind(&Connection::AfterWriteChar,
                                         shared_from_this(),
                                         boost::asio::placeholders::error));
  }
    void AfterWriteChar(const boost::system::error_code& err)
  {

    boost::asio::async_read(socket,
                            boost::asio::buffer(read_buffer),
                            boost::bind(&Connection::AfterReadChar,
                                        shared_from_this(),
                                        boost::asio::placeholders::error));
  }
      void CloseSocket()
      {
        std::cout<<"CloseSocket"<<std::endl;
       socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
       socket.close();
      }

public:
  tcp::socket socket;
  char read_buffer[64];
};



class Server
{
public:

  Server ( io_service & s, tcp::endpoint const& listen_endpoint ) : io_ ( s ), signals_ ( s ), acceptor_ ( s, listen_endpoint )
  {
    signals_.add ( SIGINT );
    signals_.add ( SIGTERM );
#if defined(SIGQUIT)
    signals_.add ( SIGQUIT );
#endif
    signals_.async_wait ( boost::bind ( &Server::Stop, this ) );
    boost::shared_ptr<Connection> c ( new Connection ( io_ ) );
    acceptor_.async_accept ( c->socket, boost::bind ( &Server::AfterAccept, this, c, _1 ) );
  }

  void Run()
  {
     io_.run();
  }

  void AfterAccept ( boost::shared_ptr<Connection>& c,boost::system::error_code const& ec )
  {
    // Check whether the server was stopped by a signal before this completion
    // handler had a chance to run.
    if ( !acceptor_.is_open() )
      {
        return;
      }

    if ( !ec )
      {
        Add(c);
        c->StartWork();
        std::cout<<"---------------------------------after startwork"<<std::endl;
        boost::shared_ptr<Connection> c2 ( new Connection ( io_ ) );
        acceptor_.async_accept ( c2->socket,boost::bind ( &Server::AfterAccept, this, c2, _1 ) );
      }
  }

  
  void Add(boost::shared_ptr<Connection>& con)
  {
    std::cout<<"add connect"<<std::endl;
    connect_sets.insert(con);
  }
  void Remove(boost::shared_ptr<Connection> con)
  {
    connect_sets.erase(con);
  }
  void CloseAll(){
    std::cout<<"set size="<<connect_sets.size()<<std::endl;
    for_each(connect_sets.begin(),connect_sets.end(),boost::bind(&Connection::CloseSocket,_1));
    connect_sets.clear();
  }
private:

  void Stop()
  {
    cout << "stopping" << endl;
    acceptor_.close();
    CloseAll();
    io_.stop();
    std::cout<<"end stoping"<<std::endl;
  }
private:
  io_service& io_;
  boost::asio::signal_set signals_;
  tcp::acceptor acceptor_;
  std::set<boost::shared_ptr<Connection>>connect_sets;
};




int main ( int argc, char** argv )
{
  pid_t pid=fork();
  if ( pid<0 )
    {
      std::cout<<"fork fail"<<std::endl;
    }
  else if ( pid==0 )
    {
      sleep ( 300 );
      try
        {
          std::cout<<"I`m child process"<<std::endl;
          boost::asio::io_service service;
          boost::asio::ip::tcp::endpoint ep ( boost::asio::ip::address_v4::from_string ( "127.0.0.1" ),8888 );
          boost::asio::ip::tcp::socket sock ( service );
          sock.async_connect ( ep,connect_handler );
          int c=0;
          while ( true )
            {
              sleep (3);
              service.run();
              char longdata[64];
              if ( c%2==0 )
                memset ( longdata,0x22,sizeof ( longdata ) );
              else
                memset ( longdata,0x11,sizeof ( longdata ) );
              sock.write_some ( buffer ( longdata,sizeof ( longdata ) ) );
              char data[64]= {0};
              sock.async_read_some ( buffer ( data,64 ),boost::bind ( read_callback,boost::asio::placeholders::error ) );
              std::cout<<"client read="<<data<<std::endl;
              c++;
            };
        }
      catch ( boost::system::system_error err )
        {
          std::cout<<"client expection="<<err.what() <<std::endl;
        }
    }
  else
    {
      io_service s;
      tcp::endpoint listen_endpoint ( tcp::v4(), 8888 );
      Server server ( s, listen_endpoint );
      server.Run();
      std::cout<<"after run"<<std::endl;
    }
  return 0;
}


