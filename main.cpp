#include <iostream>
#include <string>
#include "nginx-configparser/config_parser.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		return 1;
	}

	NginxConfigParser config_parser;
	NginxConfig config;
	config_parser.Parse(argv[1], &config);

	int port_number = 80; // this is currently a default; call config_parser to assign this value based on the config file

	
}