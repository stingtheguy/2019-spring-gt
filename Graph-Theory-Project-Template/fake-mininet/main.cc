#include <iostream>
#include <unistd.h>
#include "shell.h"

int main(int argc, char** argv){
    int ch;
    string fin("");
    // parameter configure
    while((ch=getopt(argc, argv, "f:"))!=-1)
    {
        switch(ch)
        {
            case 'f':
                fin = string(optarg);
                break;
        }
    }

    if(fin!=string("")){
        // interpret first
        sh_interpret(fin);
    }

    // enter CLI 
    sh_loop();

    return 0;
}

/*#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();

int main(int argc, char** argv){
	
	nm->interpret("topoo.txt");
    nm->print_all_e();
	nm->print_all_v();
	
	
    return 0;
}*/