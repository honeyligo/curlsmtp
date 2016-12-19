#include <unistd.h>
#include "curlsmtp.h"

int main()
{
	const std::vector<std::string> secret =
	{
		//"lybingo@163.com"
	};

	std::vector<std::string> to = 
	{
	};

	const std::vector<std::string> cc =
	{
		"godsb@qq.com"
	};

	const std::vector<std::string> attach =
	{
		"./a.pdf"
	};

	CurlSmtp* mail = new CurlSmtp("lybingo@163.com"
		,"fsfsf"
		, to
		, secret
		, cc
		, attach
		, "it's a subject"
		, "hello world you aredfsf"
		, "smtp.exmail.qq.com"
		, "587");

	mail->send_mail();

	sleep(5);
	delete mail;

	return 0;
}