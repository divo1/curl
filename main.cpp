/*
 * main.cpp
 *
 *  Created on: 27 sty 2014
 *      Author: root
 */

#include "hdr/Curl.h"
#include "hdr/curlopts.h"

#include <iostream>
#include <type_traits>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;
using namespace pl_net_divo;

int main() {
	Curl c;
	c.setOps(CurlOpts::URL, "http://m.wp.pl/?#");
	c.setOps(CurlOpts::FOLLOWLOCATION, 1L);

	string readBuffer;
	c.setCallback([](void *contents, size_t size, size_t nmemb, void *userp) -> size_t {
		((std::string*)userp)->append((char*)contents, size * nmemb);

		return size * nmemb;
	});
	c.setOps(CurlOpts::WRITEDATA, &readBuffer);
	if(c.send()) {
		cout << "Success:" << endl << readBuffer;
	} else {
		cout << "Error: " << c.errorMsg() << endl;
	}

	return 0;
}
