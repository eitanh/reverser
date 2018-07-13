#include <cpprest/http_listener.h>
#include <functional>

using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

void handle_get(http_request message)
{
    
    std::wcout << L"\ngot it\n";
    message.reply(status_codes::OK, U("Hello, World!"));
};

void handle_post(http_request message)
{
    message.reply(status_codes::NotFound);
};

void handle_put(http_request message)
{
    message.reply(status_codes::NotFound);
};

void handle_delete(http_request message)
{
    message.reply(status_codes::NotFound);
};

#define TRACE(msg)            std::wcout << msg
#define TRACE_ACTION(a, k, v) std::wcout << a << L" (" << k << L", " << v << L")\n"

int main(int argc, char ** argv)
{
  uri_builder uri(U("http://127.0.0.1:61561"));
  http_listener listener(uri.to_uri());

  listener.support(methods::GET, handle_get);
  listener.support(methods::POST, handle_post);
  listener.support(methods::PUT, handle_put);
  listener.support(methods::DEL, handle_delete);

  try
  {
     listener
        .open()
        .then([&listener](){TRACE(L"\nstarting to listen\n");})
       .wait();

      while (true);
  }
  catch (std::exception const & e)
  {
     std::wcout << e.what() << std::endl;
  }
  catch (...)
  {
     std::wcout << "Unknown exception" << std::endl;
  }

  return 0;
}
