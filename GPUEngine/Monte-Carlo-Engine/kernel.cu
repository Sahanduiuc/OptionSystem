
#include "MCEngine.cuh"


#include <stdio.h>
#include <iostream>
#include <cmath>


const int n_trails = 200;
int main() {
	//TODO
	//give a client interface where one can change market index(rate, volatility, time to maturity, n_steps, n_trails dynamically)
	MCEngine network(n_trails);
	network.doSimulation();
	//network.printNet();
	std::cout << " spot=20\n strike=20\n r=0.02\n vol=0.2\n timeToMaturity=1y\n n_steps=300\n n_trails=2000" << std::endl;
	std::cout << " vanilla call option:" << network.vanillaCallPrice(20) << std::endl;
	std::cout << " asian call option:" << network.asianCallPrice(20) << std::endl;
	std::cout << " up-and-out call option:" << network.upAndOutCallPrice(20,30) << std::endl;
	std::cout << "*************************************************************************************" << std::endl;
	std::cout << " Optimization: using reduction to calculate price generated by MC simulation:" << std::endl;
	std::cout << " vanilla call option:"<< network.vanillaCallPrice2(20) << std::endl;
	std::cout << " asian call option:" << network.asianCallPrice2(20) << std::endl;
	std::cout << " up-and-out call option:" << network.upAndOutCallPrice2(20, 30) << std::endl;
	char tmp;
	std::cin >> tmp;
	return 0;
}