#include <unistd.h>
#include "curlsmtp.h"

int main()
{
	std::vector<std::string> secret =
	{
		"wookonghair@gmail.com"
	};

	std::vector<std::string> to =
	{
		"godsb@qq.com"
	};

	std::vector<std::string> cc =
	{
		"honeyligo@sina.com"
	};

	std::vector<std::string> attach =
	{
		"./b.txt"
	};

	CurlSmtp* mail = new CurlSmtp("bingley_li@maxmob.cn"
		, "adfsf"
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

	// send another mail
	mail->set_from("bingley_li@maxmob.cn");
	mail->set_password("adfsf");
	mail->set_subject("test2");
	mail->set_message("another boy hehe hahah");
	mail->set_server(SMTP_SERVER);
	mail->set_port(SMTP_PORT);

	cc.clear();
	cc.push_back("godsb@qq.com");
	mail->set_cc(cc);

	to.clear();
	to.push_back("honeyligo@sina.com");
	mail->set_to(to);
	
	attach.clear();
	attach.push_back("./1.png");
	mail->set_attach(attach);
	
	mail->send_mail();

	sleep(5);
	delete mail;

	return 0;
}