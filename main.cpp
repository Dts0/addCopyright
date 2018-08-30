/*
* copyright (c) 2018 DTS
*/
#include "addCopyright.hpp"
#include <vector>

void showHelp();
void unknownOption(string op);
void optionLackVal(string op);
void showVersion();
void noOutputFile();

int main(int argc,char** argv){
	if(argc==0){
		showHelp();
		return 0;
	}

	int readCnt = 0;
	string copyrightFile;
	vector<string> files;
	while((++readCnt)<argc){
		string argStr(argv[readCnt]);
		if(argStr[0]=='-'){
			if(argStr=="-c"){
				if(argv[readCnt+1])
					copyrightFile=argv[++readCnt];
				else {
					optionLackVal(argStr);
					showHelp();
					return 0;
				}
			}
			else if(argStr=="-h"){
				showHelp();
				return 0;
			} else if(argStr=="-v"){
				showVersion();
				return 0;
			} else {
				unknownOption(argStr);
				showHelp();
				return 0;
			}
		}
		else {
			files.push_back(argv[readCnt]);
		}
	}

	if(files.empty()){
		noOutputFile();
		showHelp();
		return 0;
	}
	int sucessCnt=0,failCnt=0;
	for(auto it=files.begin();it!=files.end();++it){
		if(addCopyright(*it,copyrightFile,cout)>0)
			++sucessCnt;
		else ++failCnt;
		cout<<endl;
	}
	cout<<"全部完成。"
		<<"\t其中"<<sucessCnt<<"个成功，"
		<<"\t"<<failCnt<<"个失败。"
		<<endl;
	return 0;
}

void showHelp(){
	cout<<"用法：addCopyright [选项]... [文件]... \n"
		<<"\t-c\t版权文件路径，如果无法打开，直接退出\n"
		<<"\t-h\t打印帮助并退出\n"
		<<"\t-v\t打印版本信息并退出\n";
}
void unknownOption(string op){
	cout<<"未知的选项\""<<op<<"\""<<endl;
}
void showVersion(){
	cout<<"addCopyright:1.0.0\n"
		<<"Copyright (C) DTS\n"
		<<"License MIT\n"
		<<"Written by DTS\n"
		<<"my website: <http://www.dreamoftime0.com/>"
		<<endl;
}
void noOutputFile(){
	cout<<"没有输出文件。"<<endl;
}
void optionLackVal(string op){
	cout<<"选项\""<<op<<"\"缺少值"<<endl;
}
