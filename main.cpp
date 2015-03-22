#include <iostream>
#include "include/ConfigurationManager.hpp"

using namespace std;

int main()
{
	ConfigurationManager cfg;
	cfg.saveClusteringParams("test.txt");
    cout << "COMPILES!!!!\n";
    return 0;
}