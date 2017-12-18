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
  std::cout<<"client connect err "<<err.message() <<std::endl;
}

class Connection:public boost::enable_shared_from_this<Connection>
{
public:
  Connection ( io_service& s ) : socket ( s ),strand_(s)
  {
//     std::cout<<"Connection"<<std::endl;
  }

  ~Connection()
  {
    socket.close();
    cout << "~Connection" << endl;
  }

  void StartWork()
  {
    boost::asio::async_read ( socket,
                              boost::asio::buffer ( read_buffer ),
                              strand_.wrap(boost::bind ( &Connection::AfterReadChar,
                                                         shared_from_this(),
                                                         _1 ) ));
    
    
//     \033[1m \033[41;39m \033[0m
    std::string d(" \033[1m \033[41;39m I`m Service ,current time is ");
    time_t now = std::time ( NULL );
    d+=ctime(&now);
    d.erase(d.end()-1);
    d+="\033[0m";
    boost::asio::async_write ( socket,
                               boost::asio::buffer (d ),
                               strand_.wrap(boost::bind ( &Connection::AfterWriteChar,
                                                          shared_from_this(),
                                                          _1 ) ));





  }

  void AfterReadChar ( const boost::system::error_code& err )
  {
//     std::cout<<"service read="<<read_buffer<<std::endl;
    boost::asio::async_write ( socket,
                               boost::asio::buffer(read_buffer),
                               strand_.wrap(boost::bind ( &Connection::AfterWriteChar,
                                   shared_from_this(),
                                   boost::asio::placeholders::error) ) );
  }

  void AfterWriteChar ( const boost::system::error_code& err )
  {
//     std::cout<<"service wirte success"<<std::endl;
    boost::asio::async_read ( socket,
                              boost::asio::buffer ( read_buffer ),
                              strand_.wrap(boost::bind ( &Connection::AfterReadChar,
                                            shared_from_this(),
                                            boost::asio::placeholders::error ) ));
  }

  void CloseSocket()
  {
    std::cout<<"CloseSocket"<<std::endl;
    socket.shutdown ( boost::asio::ip::tcp::socket::shutdown_both );
    socket.close();
  }

public:
  tcp::socket socket;
  char read_buffer[64];
  boost::asio::io_service::strand strand_;
};



class Server
{
public:

  Server ( io_service & s, tcp::endpoint const& listen_endpoint ,size_t size ) : io_ ( s ), signals_ ( s ), acceptor_ ( s, listen_endpoint ),pool_size_ ( size )
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
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for ( size_t i = 0; i < pool_size_; ++i )
      {
        boost::shared_ptr<boost::thread> t ( new boost::thread ( bind ( &io_service::run, &io_ ) ) );
        threads.push_back ( t );
      }

    for ( std::size_t i = 0; i < threads.size(); ++i )
      {
        threads[i]->join();
      }
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
        Add ( c );
        c->StartWork();
        boost::shared_ptr<Connection> c2 ( new Connection ( io_ ) );
        acceptor_.async_accept ( c2->socket,boost::bind ( &Server::AfterAccept, this, c2, _1 ) );
      }
  }


  void Add ( boost::shared_ptr<Connection>& con )
  {
    std::cout<<"add connect"<<std::endl;
    connect_sets.insert ( con );
  }

  void Remove ( boost::shared_ptr<Connection> con )
  {
    connect_sets.erase ( con );
  }

  void CloseAll()
  {
    std::cout<<"set size="<<connect_sets.size() <<std::endl;
    for_each ( connect_sets.begin(),connect_sets.end(),boost::bind ( &Connection::CloseSocket,_1 ) );
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
  size_t pool_size_;
};



void client_process()
{
  std::cout<<"I`m child process"<<std::endl;
  boost::asio::io_service service;
  boost::asio::ip::tcp::endpoint ep ( boost::asio::ip::address_v4::from_string ( "127.0.0.1" ),8888 );
  boost::asio::ip::tcp::socket sock ( service );
  sock.async_connect ( ep,connect_handler );

  while ( true )
    {
      service.run();
      char data[128]= {0};
      sock.read_some ( buffer ( data,128 ) );
      std::cout<<data<<std::endl;
      char longdata[64]={0};
      std::string str;
      std::getline(cin,str);
      memcpy(longdata,str.c_str(),str.size());
      sock.write_some ( buffer ( longdata,sizeof ( longdata ) ) );
    };
}

int main ( int argc, char** argv )
{
  pid_t pid=fork();
  if ( pid<0 )
    {
      std::cout<<"fork fail"<<std::endl;
      exit(-1);
    }
  else if ( pid==0 )
    {
      try
        {
          client_process();
        }
      catch ( boost::system::system_error err )
        {
          std::cout<<"client expection="<<err.what() <<std::endl;
        }
      exit(0);
    }
  else
    {
      try
        {
          io_service s;
          tcp::endpoint listen_endpoint ( tcp::v4(), 8888 );
          Server server ( s, listen_endpoint,10 );
          server.Run();
        }
      catch ( std::exception err )
        {
          std::cout<<"service excepiton="<<err.what() <<std::endl;
        }
    }
  return 0;
}


