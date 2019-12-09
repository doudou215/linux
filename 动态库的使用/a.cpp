#include "a.h"
#include <string.h>
#include <dirent.h>
#include <string>
void B::getName(vector<string> &str)
{
	DIR *dir1=opendir("./plug");
	if(!dir1)
	{
		cerr<<"please enter correct dir"<<endl;
		return;
	}	
	for(;;){
		struct dirent *dir=readdir(dir1);
		if(!dir)
				break;
		else if(strcmp(dir->d_name,"..")==0)
				continue;
		else if(strcmp(dir->d_name,".")==0)
				continue;
		else{
			string cur_dir("./plug/");
			cur_dir+=dir->d_name;
			str.push_back(cur_dir);
		}
	}
	return;	
}
