#include "PackParser.hpp"
#include <stdio.h>
PackParser::PackParser(const char* filepath){
	this->s="";
	FILE* f=fopen(filepath,"r");
	while(!feof(f)){
		this->s+=fgetc(f);
	}
	printf("%s\n",this->s.data());
}
PackParser::~PackParser(){
	
}
int PackParser::getX0(std::string& s){
	return 0;
}
