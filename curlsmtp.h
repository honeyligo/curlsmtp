#ifndef __CURL_SMTP_H__
#define __CURL_SMTP_H__

#include <vector>
#include <string.h>
#include <curl/curl.h>
#include "ustd_string.h"

#define USERNAME "bingley_li@maxmob.cn"
#define PASSWORD "libin123"
#define SMTP_SERVER "smtp.exmail.qq.com"
#define SMTP_PORT "587" /* it is a colon+port string, but you can set it
                           to "" to use the default port */
//#define FROM "<bingley_li@maxmob.cn>"
//#define TO "<honeyligo@sina.com>"
//#define TO1 "<lybingo@163.com>"
//#define CC "<godsb@qq.com>"
//#define ALL "<all@maxmob.com>"

#define LEFT_BRACE "<"
#define RIGTH_BRACE ">"
#define ENTER			"\r\n"
#define BOUNDARY_FLAG	"--"

#define USER_AGENT "User-Agent: My eMail Client"
#define MIME_VER "MIME-Version: 1.0"
#define HEADER_CONTENT_TYPE "Content-Type: multipart/mixed;"

#define MSG_CONTENT_TYPE "Content-Type: text/plain; charset=utf-8; format=flowed"
#define MSG_ENCODING "Content-Transfer-Encoding: 7bit"

class CurlSmtp
{
	struct WriteThis
	{
		int pos;
		int counter;
		std::vector<std::string> data;
	};

public:
	CurlSmtp(const std::string& from,
	const std::string& password,
	const std::vector<std::string>& to,
	const std::vector<std::string>& secret,
	const std::vector<std::string>& cc,
	const std::vector<std::string>& attach,
	const std::string& subject,
	const std::string& message,
	const std::string& server = SMTP_SERVER,
	const std::string& port = SMTP_PORT);

	~CurlSmtp();

	void set_from(const std::string& from);
	void set_to(const std::vector<std::string>& to);
	void set_secret(const std::vector<std::string>& secret);
	void set_cc(const std::vector<std::string>& cc);
	void set_from(const std::vector<std::string>& from);
	void set_attach(const std::vector<std::string>& attach);
	void send_mail();

private:
	void make_send_message();
	bool attach(const std::string& filename);
	void set_receiver_list();
	void set_curl_option();
	static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp);

	std::string get_boundary()
	{
		std::string boundary;
		boundary.reserve(16);
		const char hex[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < 16; ++i)
		{
			int x = rand() % 62;
			boundary.append(1, hex[x]);
		}

		return boundary;
	}

private:
	std::vector<std::string> send_buffer_;
	std::vector<std::string> to_;
	std::vector<std::string> cc_;
	std::vector<std::string> secret_;
	std::vector<std::string> attach_;
	std::string from_;
	std::string server_;
	std::string port_;
	std::string subject_;
	std::string message_;
	std::string password_;
	std::vector<std::pair<std::vector<char>, std::string>> attachment_;

	CURL *curl_;
	CURLM *mcurl_;
	struct curl_slist* rcpt_list_;
	struct WriteThis pooh_;
};

#endif // !__CURL_SMTP_H__