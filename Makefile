all:
	g++ -o server *cpp -lboost_thread -lboost_system -lpthread
