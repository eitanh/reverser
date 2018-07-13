#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#pragma comment(lib, "cpprest110_1_1")
 
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
 
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
 
#define TRACE(msg)            wcout << msg
#define TRACE_ACTION(a, k, v) wcout << a << L" (" << k << L", " << v << L")\n"
 
map<utility::string_t, utility::string_t> dictionary;
 
/* handlers implementation */
 
int main()
{
   http_listener listener(L"http://localhost/restdemo");
 
   listener.support(methods::GET, handle_get);
   listener.support(methods::POST, handle_post);
   listener.support(methods::PUT, handle_put);
   listener.support(methods::DEL, handle_del);
 
   try
   {
      listener
         .open()
         .then([&listener](){TRACE(L"\nstarting to listen\n");})
         .wait();
 
      while (true);
   }
   catch (exception const & e)
   {
      wcout << e.what() << endl;
   }
 
   return 0;
}
