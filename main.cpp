//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "server.hpp"

int mainCycle(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    if (argc != 7)
    {
      std::cerr << "Usage: http_server <address> <port> <threads> <doc_root>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 80 1 .\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    receiver 0::0 80 1 .\n";
      return 1;
    }

    // Initialise the server.
    std::size_t num_threads = 4;//boost::lexical_cast<std::size_t>(argv[7]);
    http::server3::server s(argv[2], argv[4], argv[6], num_threads);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>

static sig_atomic_t EXIT = 0;

void sig_handler( int signo ) {
	EXIT = 1;
}

int main(int argc, char* argv[])
{	
	pid_t child_pid = fork();

	if( child_pid < 0 ) {
		printf("Programm can not demonize\n");
		return -1;
	}
	
	if( child_pid ) 
		exit(0);
	
	umask(0);

	setsid();

	chdir("/");

//	printf("%d\n", getpid());

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	signal( SIGURG, sig_handler );

	mainCycle(argc, argv);

	return 0;	
}


