#g++ server2.cpp  -lcpprest -lboost_system -lssl -lcrypto -o build/server
g++ client.cpp -lcurl -o build/client
