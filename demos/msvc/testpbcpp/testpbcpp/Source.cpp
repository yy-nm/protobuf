
//#ifndef _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
//#endif

#include <stdio.h>

#include <iostream>
#include <fstream>
using namespace std;

#include "code\login.pb.h"

bool writeData2File(const char *_data, const char *_fileName) {
	if (NULL == _fileName)
		return false;
	if (NULL == _data)
		return false;

	FILE *file = fopen(_fileName, "wb+");
	if (NULL == file)
		return false;
	size_t count = fwrite(_data, sizeof(char), strlen(_data), file);
	if (count != strlen(_data)) {
		fclose(file);
		return false;
	}

	fclose(file);
	return true;
}

long getLengthOfFile(const char *_fileName) {

	FILE *file = fopen(_fileName, "rb+");
	if (NULL == file)
		return 0;

	if (0 == fseek(file, 0, SEEK_END))
	{
		off_t offset = ftell(file);
		return offset;
	}
	return 0;
}

const char * readDataFromFile(const char *_fileName) {
	if (NULL == _fileName)
		return NULL;

	FILE *file = fopen(_fileName, "rb+");
	if (NULL == file)
		return NULL;

	off_t offset = getLengthOfFile(_fileName);

	char *buf = (char *)malloc(offset + 1);
	memset(buf, 0, offset + 1);

	int count = fread(buf, sizeof(char), offset + 1, file);

	fclose(file);
	buf[offset] = '\0';
	return buf;


	
	return NULL;
}


int main(void) {

	LoginRequest lr;
	lr.set_id(1);
	lr.set_name("helloworld");
	lr.set_email("yes");

	LoginRequest ll;
	string str;
	//lr.SerializeToString(&str);
	str = lr.SerializeAsString();
	ll.ParseFromString(str);
	printf("Serial str: %s\n", str.c_str());
	printf("id: %d, name: %s, email: %s\n", ll.id(), ll.name().c_str(), ll.email().c_str());

	if (writeData2File(lr.SerializeAsString().c_str(), "test")) {
		printf("data write to file success\n");


		const char *data = readDataFromFile("test");
		printf("read from str: %s\n", data);
		if (NULL != data)
		{
			LoginRequest l;
			//l.ParseFromArray(data, strlen(data));
			l.ParseFromString(string(data));
			printf("id: %d, name: %s, email: %s\n", l.id(), l.name().c_str(), l.email().c_str());
			printf("has email: %d\n", l.has_email());
		}
		else

			perror("read error");

		/*
		fstream fs = fstream("test", ios::in | ios::binary);
		LoginRequest l;
		if (l.ParsePartialFromIstream(&fs))
			printf("id: %d, name: %s, email: %s\n", l.id(), l.name().c_str(), l.email().c_str());
		else
			perror("parse error!\n");

		fs = fstream("test", ios::in);
		printf("\n");
		while (!fs.eof())
		{
			cout << fs.get() << endl;
		}
*/
	}


	
	getchar();

	return 0;
}