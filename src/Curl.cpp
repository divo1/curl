/*
 * Curl.cpp
 *
 *  Created on: 27 sty 2014
 *      Author: root
 */

#include "../hdr/Curl.h"

namespace pl_net_divo {

function<size_t(void*, size_t, size_t, void*)> Curl::CURL_CALL::callback = nullptr;
Curl::Curl() : res(CURLE_FAILED_INIT) {
	curl = curl_easy_init();
	if(curl == NULL) {
		curl = nullptr;
	}
}

Curl::~Curl() {
	if(curl != nullptr && curl != NULL) {
		curl_easy_cleanup(curl);
	}
}
void Curl::setOps(CurlOpts key, string value) {
	setOps(key, value.c_str());
}
bool Curl::send() {
	if(curl == nullptr) {
		return false;
	}

	res = curl_easy_perform(curl);

	if (res != CURLE_OK)
		return false;

	return true;
}
void Curl::setCallback(function<size_t(void*, size_t, size_t, void*)> value) {
	CURL_CALL::callback = value;
	setCurlOps(CurlOpts::WRITEFUNCTION, &CURL_CALL::get);
}
string Curl::errorMsg() {
	if(res != CURLE_OK) {
		return string(curl_easy_strerror(res));
	}

	return "";
}

} /* namespace pl_net_divo */
