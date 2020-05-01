//**********************************************
//  Simple program t use with Conky Manager.
//
// Usage: ./monitor <option>
// Options:
// 	--ram 		Show total ram info
// 	--ramuse 	Show percentual ram in use
// 	--swap 		Show swap info
// 	--swapuse 	Show percentual swap in use
// 	--extip 	Show external IP address
//
//  License: GPLv3
//  Author: Alan Franco - https://github.com/fzappa
//  Rev.: 12/05/2015 (PT_BR)
//
//  Compile with:
//  g++ monitor.cpp -o monitor -I/usr/include/libgtop-2.0/ -lgtop-2.0 `pkg-config --cflags --libs gtk+-3.0`
//
//*********************************************

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <array>

#include <glibtop.h>
#include <glibtop/mem.h>
#include <glibtop/swap.h>

#include <boost/algorithm/string.hpp>
		   
#define GB 1073745920 //GiB -> GB
#define MB 1048576     //MiB -> MB

static void showUsage(std::string);
int getRam(void);
int getRamPer(void);
int getSwap(void);
int getSwaper(void);
int getIp(void);
std::string exec(const char*);

int main(int argc, char * argv[])
{
	if(argc <= 1){
		showUsage(argv[0]);
	} 
	else {
		std::string arg;
		arg = argv[1];
		if(arg=="--ram"){
			getRam();
		}
		else if(arg=="--ramuse"){
			getRamPer();
		}
		else if(arg=="--swap"){
			getSwap();
		}
		else if(arg=="--swapuse"){
			getSwaper();
		}
		else if(arg=="--extip"){
			getIp();
		}
	}
    return 0;
}


static void showUsage(std::string name){
    std::cerr << "Usage: " << name << " <option>\n"
              << "Options:\n"
              << "\t--ram \t\tShow total ram info\n"
              << "\t--ramuse \tShow percentual ram in use\n"
			  << "\t--swap \t\tShow swap info\n"
			  << "\t--swapuse \tShow percentual swap in use\n"
			  << "\t--extip \tShow external IP address\n"
              << std::endl;
}

int getRam(void){
	glibtop_init();
	glibtop_mem mem;
	glibtop_get_mem(&mem);

	float util;
	util = (float)(mem.used - mem.cached - mem.buffer);

	if((util/GB) < 1){
		std::cout.precision(3);
		std::cout << util/MB <<"MB / " << (float)mem.total/GB <<"GB\n";
	}
	else{
		std::cout.precision(3);
		std::cout << util/GB <<"GB / " << (float)mem.total/GB <<"GB\n";
	}

	return 0;
}


int getRamPer(void){
	glibtop_init();
	glibtop_mem mem;
	glibtop_get_mem(&mem);

	float memperc;

	memperc = 100*(float)(mem.used - mem.buffer - mem.cached)/mem.total;

	std::cout.precision(3);
	std::cout << memperc <<"%\n";

	return 0;
}

int getSwap(void){
	glibtop_init();
	glibtop_swap swap;
	glibtop_get_swap(&swap);

	if(((float)swap.used/GB) < 1){
		std::cout.precision(3);
		std::cout << (float)swap.used/MB <<"MB / " << (float)swap.total/GB <<"GB\n";
	}
	else{
		std::cout.precision(3);
		std::cout << (float)swap.used/GB <<"GB / " << (float)swap.total/GB <<"GB\n";
	}

	return 0;
}

int getSwaper(void){
	glibtop_init();
	glibtop_swap swap;
	glibtop_get_swap(&swap);

	std::cout.precision(3);
	std::cout << 100*(float)(swap.used)/swap.total <<"%\n";

	return 0;
}

int getIp(void){
	std::string ip;
	ip = exec("dig TXT +short o-o.myaddr.l.google.com @ns1.google.com");
	boost::erase_all(ip, "\"");
	std::cout << ip;
	return 0;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
