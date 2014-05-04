/*
 * Curl.h
 *
 *  Created on: 27 sty 2014
 *      Author: root
 */

#ifndef CURL_H_
#define CURL_H_

#include "curlopts.h"

#include <string>
#include <curl/curl.h>
#include <iostream>
#include <functional>
#include <type_traits>

namespace pl_net_divo {

using namespace std;

/*
 *
 */
class Curl {
private:
	CURL *curl;
	CURLcode res;

	// Helper struct that allow us to convert std::function to curl callback. This isn't thread safe.
	// TODO:
	// - Allow adding few callbacks
	// - Add thread safe
	struct CURL_CALL {
		friend Curl;
	private:
		static function<size_t(void*, size_t, size_t, void*)> callback;
		static size_t get(void* a, size_t b, size_t c, void* d) {
			return callback(a, b, c, d);
		}
	};

	/**
	 * wrapper method to call curl_easy_setopt
	 * @param key - CurlOpts
	 * @param value - some values use in curl_easy_setopt
	 */
	template<typename T>
	void setCurlOps(CurlOpts key, T value) {
		if(curl == nullptr) {
			return;
		}

		curl_easy_setopt(curl, static_cast<CURLoption>(key), value);
	}
public:
	Curl();
	virtual ~Curl();

	template<typename T>
	void setOps(CurlOpts key, T value) {
		setCurlOps(key, value);
	}
	void setOps(CurlOpts key, string value);
	void setCallback(function<size_t(void*, size_t, size_t, void*)> value);

	bool send();
	string errorMsg();
};

} /* namespace pl_net_divo */

#endif /* CURL_H_ */
