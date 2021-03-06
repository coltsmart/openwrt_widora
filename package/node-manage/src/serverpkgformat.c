#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <json-c/json.h>
#include <malloc.h>
#include<unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void serverpkgformat(void)
{
	int len;
	int32_t tmp;
	struct json_object *pragma = NULL;
	struct json_object *chip = NULL;
	struct json_object *obj = NULL;
	struct json_object *array = NULL;
	int i = 0;
	int loop = 0;
	uint8_t byte[100];
	uint8_t *buf = malloc(4096);
	int file;

	memset(buf,0,4096);
	file = open("/usr/UpData", O_RDWR|O_CREAT);
	if(file < 0)
	{
            //printf("%s,%d,%d\r\n",__func__,__LINE__,errno);
	}
	lseek(file,0,SEEK_SET);
	ftruncate(file,0);
	pragma = json_object_new_object();
	json_object_object_add(pragma,"FrameType",json_object_new_string("UpData"));
	json_object_object_add(pragma,"NodeType",json_object_new_string("Class A"));
    json_object_object_add(pragma,"DevEUI",json_object_new_string("01234567ABCDEF89"));
    json_object_object_add(pragma,"NetAddr",json_object_new_int(0));
    json_object_object_add(pragma,"AppEUI",json_object_new_string("01234567ABCDEF89"));
    json_object_object_add(pragma,"Port",json_object_new_int(0));
    json_object_object_add(pragma,"ConfirmRequest",json_object_new_boolean(1));
	json_object_object_add(pragma,"Confirm",json_object_new_boolean(1));
    json_object_object_add(pragma,"Battery",json_object_new_int(0));
    json_object_object_add(pragma,"Rssi",json_object_new_int(-12));
    json_object_object_add(pragma,"Snr",json_object_new_int(-13));
    json_object_object_add(pragma,"Data",json_object_new_string("01234567ABCDEF89"));	/* data that encoded into Base64 */
    strcpy(buf,json_object_to_json_string(pragma));
	write(file,buf,strlen(buf));
    //printf("%s",buf);
	json_object_put(pragma);
	close(file);
/*
	memset(buf,0,4096);
	file = open("/usr/UpConfirm", O_RDWR|O_CREAT);
	if(file < 0)
	{
            //printf("%s,%d,%d\r\n",__func__,__LINE__,errno);
	}
	lseek(file,0,SEEK_SET);
	ftruncate(file,0);
	pragma = json_object_new_object();
	json_object_object_add(pragma,"FrameType",json_object_new_string("UpConfirm"));
	json_object_object_add(pragma,"NodeType",json_object_new_string("Class A"));
    json_object_object_add(pragma,"DevEUI",json_object_new_string("01234567ABCDEF89"));
    json_object_object_add(pragma,"NetAddr",json_object_new_int(0));
	json_object_object_add(pragma,"Result",json_object_new_string("Success"));
    json_object_object_add(pragma,"Rssi",json_object_new_int(-12));
    json_object_object_add(pragma,"Snr",json_object_new_int(-13));
    strcpy(buf,json_object_to_json_string(pragma));
	write(file,buf,strlen(buf));
    //printf("%s",buf);
	json_object_put(pragma);
	close(file);
*/
	memset(buf,0,4096);
	file = open("/usr/DownData", O_RDWR|O_CREAT);
	if(file < 0)
	{
            //printf("%s,%d,%d\r\n",__func__,__LINE__,errno);
	}
	lseek(file,0,SEEK_SET);
	ftruncate(file,0);
	pragma = json_object_new_object();
	json_object_object_add(pragma,"FrameType",json_object_new_string("DataDown"));
	json_object_object_add(pragma,"NetAddr",json_object_new_int(0));
    json_object_object_add(pragma,"Port",json_object_new_int(0));
    json_object_object_add(pragma,"ConfirmRequest",json_object_new_boolean(1));
	json_object_object_add(pragma,"Confirm",json_object_new_boolean(1));
    json_object_object_add(pragma,"Data",json_object_new_string("01234567ABCDEF89"));	/* data that encoded into Base64 */
    strcpy(buf,json_object_to_json_string(pragma));
	write(file,buf,strlen(buf));
    //printf("%s",buf);
	json_object_put(pragma);
	close(file);
/*
	memset(buf,0,4096);
	file = open("/usr/DownConfirm", O_RDWR|O_CREAT);
	if(file < 0)
	{
            //printf("%s,%d,%d\r\n",__func__,__LINE__,errno);
	}
	lseek(file,0,SEEK_SET);
	ftruncate(file,0);
	pragma = json_object_new_object();
	json_object_object_add(pragma,"FrameType",json_object_new_string("DownConfirm"));
    json_object_object_add(pragma,"NetAddr",json_object_new_int(0));
    strcpy(buf,json_object_to_json_string(pragma));
	write(file,buf,strlen(buf));
    //printf("%s",buf);
	json_object_put(pragma);
	close(file);
	*/
}
