/*
* copyright (c) 2018 DTS
*/
#include "addCopyright.hpp"

int addCopyright(string fileName,string copyrightFile,ostream& os){
	ifstream rfile(fileName.c_str());
	if(!rfile.is_open()){
		os<<"错误: 文件 "<<fileName<<" 无法被读取。"<<endl;
		return -1;
	}

	ifstream header(copyrightFile.c_str());
	stringstream buf;
	if(!header.is_open()){
		os<<"错误: 没有选择版权信息文件或版权信息文件无法被读取。所以未添加。"<<endl;
		//buf<<"/*这是默认的版权信息\n"
		//   <<"* copyright (c) 2018 DTS\n"
		//   <<"*/\n";
		 return -3;
	} else{
		buf<<header.rdbuf();
	}

	string charbuf1,charbuf2;
	header.seekg(header.beg);
	header>>charbuf1;
	header.close();

	rfile>>charbuf2;
	rfile.seekg(rfile.beg);

	if(charbuf1==charbuf2){
		os<<"警告: 这个版权信息文件已被添加到文件 "<<fileName<<" 过，因此没有继续执行。"<<endl;
		return 1;
	}

	buf<<rfile.rdbuf();
	rfile.close();

	ofstream wfile(fileName.c_str(), ios::out|ios::trunc);
	if(!wfile.is_open()){
		os<<"错误: 文件 "<<fileName<<" 无法被写入。"<<endl;
		return -2;
	}
	wfile<<buf.rdbuf();
	wfile.close();

	os<<"信息: 版权信息被成功添加到文件 "<<fileName<<" 。"<<endl;
	return 1;
}
