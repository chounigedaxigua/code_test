#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <syslog.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#define NAME_MAX 4096
#define MAX_LEN 1024

#define SSID_NUM_MAX 4
#define SSID_NAME_LEN 64
#define MAXLINE 4096
#define PORT 6666


typedef  char  int08_t ;
typedef  short int16_t ;
typedef  int   int32_t ;
typedef unsigned char  uint08_t ;
typedef unsigned short uint16_t ;
typedef unsigned int   uint32_t ;

#define CONFIG_FILE "/home/xhh/work/gphfile/wifi_tcp/config.ini"
typedef enum 
{
  STATE_OK,
  STATE_FAIL,
  STATE_SOCKET_FAIL,
  
}STATE;

typedef struct _ssid_name_t
{
  int08_t  name[SSID_NAME_LEN];
}ssid_name_t;

typedef struct _ssid_info_t
{
	uint32_t    num;
	ssid_name_t namelist[SSID_NUM_MAX];
}ssid_info_t;



typedef struct _ctrl_info_t
{
  int32_t             tcp_fd;
  struct sockaddr_in  tcp_server; 
	uint32_t            tcp_port;
  int08_t             scan_key[MAX_LEN];
  uint32_t            scan_time;
  int32_t             client_fd;
}ctrl_info_t;
#define SSID_INFO_RESET(A)   (memset(A,0,sizeof(ssid_info_t))
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
static FILE *s_debug_fp = NULL;
STATE _cur_time_string_get( int08_t *p_time )
{
  time_t current_time = time(NULL);
  struct tm *tm       = NULL;
  
  tm = localtime(&current_time);
  sprintf(p_time,"%04d-%02d-%02d %02d:%02d:%02d ",tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, 
    tm->tm_hour, tm->tm_min, tm->tm_sec);
  return STATE_OK;
  
}

STATE _debug_init()
{
  s_debug_fp = fopen("/var/log/wifi.log","wt+");
  
  if( s_debug_fp == NULL)
    return STATE_FAIL;
    
  return STATE_OK;
}

STATE _debug_info(uint32_t save,int08_t *msg,...)
{
  va_list argp;
  va_start( argp, msg );
  int08_t *p_start = NULL;
  int08_t tmp_val[NAME_MAX] = {0};
  _cur_time_string_get(tmp_val);
  
  
  p_start = tmp_val + strlen(tmp_val);
  vsnprintf(p_start,NAME_MAX -strlen(tmp_val), msg,argp);
  printf("%s",tmp_val);
  va_end(argp);
  
  if( save )
  {
    s_debug_fp = fopen("/var/log/wifi.log","at+");
    fprintf(s_debug_fp,"%s",tmp_val );
    fclose(s_debug_fp);
  }
  return STATE_OK;
}


STATE param_data_get( int08_t *cmd ,int08_t *ret ,int32_t len )
{
	FILE *fp = NULL;
	int  i = 0;
	if(  cmd == NULL || ret == NULL  || len  == 0 ) 
	{
		_debug_info(1,"input parmae err");
		return STATE_FAIL;

	}
	fp = popen( cmd, "r");
  if( fp  == NULL )
	{
		_debug_info(1,"open cmd %s err ",cmd );
		return STATE_FAIL;
	}
	fgets(ret,len-1,fp);
	for(i = 0;i < strlen(ret);i ++)
	{
		if( ret[i] == '\n' || ret[i] == '\r')
		{
			ret[i] = '\0';
			break;
		}	
	}

	fclose(fp);
	return 0;
}


STATE _ssid_info_printf( ssid_info_t *p_info )
{
  uint32_t i  = 0;
  //int08_t time_buffer[MAX_LEN] ={0};
  
  
  if( p_info  == NULL )
    return STATE_FAIL;
  

  //_cur_time_string_get(time_buffer);
  
  _debug_info(0,"scan wifi num %d list :\r\n",p_info->num);
  
  for( i = 0;i < p_info->num; i ++ )
  {
    _debug_info(0,"%s\r\n",p_info->namelist[i].name);
  }
  return STATE_OK;
}

STATE _ssid_info_send( int32_t fd, ssid_info_t *p_info)
{
  uint32_t i  = 0,send_len = 0;
  if( fd == -1 || p_info  == NULL )
    return STATE_FAIL;
  
  
  for( i = 0;i < p_info->num; i ++ )
  {
    send_len = send(fd,p_info->namelist[i].name,strlen(p_info->namelist[i].name),MSG_NOSIGNAL);
    if( send_len < 0 )
      return STATE_SOCKET_FAIL;
  }
  
  return STATE_OK;
}
STATE _ssid_info_scan(ssid_info_t *p_info,int08_t *p_scan_key)
{
  int08_t scan_str[MAX_LEN] = {0};
  FILE *fp  = NULL;
  if( p_info  == NULL )
    return STATE_FAIL;
    
  memset(p_info,0,sizeof(ssid_info_t));
  
  sprintf( scan_str,"sudo iwlist wlan0 scanning | grep ESSID | grep -v \"00\"|grep \"%s\" | awk -F':' '{print $2}' 2>>  /etc/init.d/err.log",p_scan_key);
  
  fp = popen(scan_str,"r");
  if( fp == NULL )
    return  STATE_FAIL;
  
  while( fgets(p_info->namelist[p_info->num].name,SSID_NAME_LEN,fp) > 0 )
  {
		 p_info->num ++;
  }
  
  if(p_info->num > 0 )
  {
    _ssid_info_printf(p_info);
  }
  else
  {
    _debug_info(0,"no wifi scan.\r\n");
  }
  fclose(fp);
  return STATE_OK;
}

STATE _socket_tcp_init( ctrl_info_t *p_ctl)
{
  int32_t addr_len = sizeof(struct sockaddr_in);
  uint32_t breuse_addr = 1;
  if( p_ctl == NULL )
    return STATE_FAIL;
    
  p_ctl->tcp_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(p_ctl->tcp_fd  < 0 )
  {
    _debug_info(1,"create socket error: %s(errno: %d)\n",strerror(errno), errno);
   
    return STATE_FAIL;
  }
  
  setsockopt( p_ctl->tcp_fd, SOL_SOCKET, SO_REUSEADDR, ( const char* )&breuse_addr, sizeof( uint32_t ) );
  
  bzero(&p_ctl->tcp_server,sizeof(struct sockaddr_in));          
 	p_ctl->tcp_server.sin_family 			= AF_INET;
	p_ctl->tcp_server.sin_port 				= htons(p_ctl->tcp_port);
  p_ctl->tcp_server.sin_addr.s_addr = htonl(INADDR_ANY);
  
	
  if (bind(p_ctl->tcp_fd, (struct sockaddr*)&p_ctl->tcp_server, addr_len) < 0 )
  {
			_debug_info(1,"bind socket error: %s(errno: %d)\n", strerror(errno), errno);
     
			return STATE_FAIL;
  }
  _debug_info(0,"start listen fd :%d \n", p_ctl->tcp_fd);
  if (listen(p_ctl->tcp_fd, 10) < 0 ) 
  {
			_debug_info(1,"listen socket error: %s(errno: %d)\n", strerror(errno), errno);
     
			return STATE_FAIL;
  }
  
  _debug_info(0,"_sal_socket_create fd %d bind and listen port %d\n",p_ctl->tcp_fd,p_ctl->tcp_port);
  return STATE_OK;
}

STATE _ctrl_info_get(ctrl_info_t *p_ctl)
{
  int08_t tmp_val[MAX_LEN] = {0};
  int08_t key_val[MAX_LEN] = {0};
  if( p_ctl == NULL )
    return STATE_FAIL;
    
  sprintf(key_val, "cat %s | grep \"key_string\" | awk -F':' '{print $2}'",CONFIG_FILE);
  param_data_get(key_val,p_ctl->scan_key,MAX_LEN);
  memset(key_val,0,MAX_LEN);
  
   
  memset(tmp_val,0,sizeof(tmp_val));
  sprintf(key_val, "cat %s | grep \"dst_port\"| awk -F':' '{print $2}'",CONFIG_FILE);
  param_data_get(key_val,tmp_val,sizeof(tmp_val));
  p_ctl->tcp_port = atoi(tmp_val);
  memset(key_val,0,MAX_LEN);
  
  memset(tmp_val,0,sizeof(tmp_val));
  sprintf(key_val, "cat %s | grep \"dst_time\" | awk -F':' '{print $2}'",CONFIG_FILE);
  param_data_get(key_val,tmp_val,sizeof(tmp_val));
  p_ctl->scan_time = atoi(tmp_val);
  memset(key_val,0,MAX_LEN);
  
  
  
  _debug_info(1,"_ctrl_info_get scan_key %s listen port %d,scan time %d\n ",p_ctl->scan_key,p_ctl->tcp_port,p_ctl->scan_time);
 
  return STATE_OK;
  
}
void * _socket_tcp_recv_thread( void *p_data)
{
    int32_t len = 0;
    uint08_t tmp_val[32] = {0};
    ctrl_info_t *p_ctr = (ctrl_info_t *)p_data;
    _debug_info(0,"start a new client fd %d recv thread\n",p_ctr->client_fd);
    while(recv(p_ctr->client_fd,tmp_val,32,0) > 0)
    {
      _debug_info(0,"recv data form fd %d \n",p_ctr->client_fd);
    }
    close(p_ctr->client_fd);
    p_ctr->client_fd = -1;
    _debug_info(0,"end a new client fd %d recv thread\n",p_ctr->client_fd);
    return NULL;
}


STATE _socket_tcp_task(ctrl_info_t *p_ctl,ssid_info_t *p_info)
{
  pthread_attr_t  thread_attr;

  uint32_t accept_len = 0,breuse_addr = 1;
  pthread_t ntid; 
  struct sockaddr_in client_addr;  
  if( p_ctl == NULL )
    return STATE_FAIL;
  
  _debug_info(0,"_socket_tcp_init\n");
  if( _socket_tcp_init(p_ctl ) != STATE_OK || p_ctl->tcp_fd == -1  )
  {
    _debug_info(1,"_socket_tcp_init err ,exit \n");
    return STATE_FAIL;
  }
  
  
  pthread_attr_init(&thread_attr);
  
  
  pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

  while( 1 )
  {
      p_ctl->client_fd = accept(p_ctl->tcp_fd,(__SOCKADDR_ARG )&client_addr,(uint32_t *)&accept_len);
      if( p_ctl->client_fd < 0 )
      {
        _debug_info(1,"accept socket error: %s(errno: %d)\n", strerror(errno), errno);
        continue;
      }
      _debug_info(1,"accept new client socket fd %d \n",p_ctl->client_fd );
      
      setsockopt( p_ctl->tcp_fd, SOL_SOCKET, SO_REUSEADDR, ( const char* )&breuse_addr, sizeof( uint32_t ) );
     	pthread_create(&ntid, &thread_attr, _socket_tcp_recv_thread, p_ctl);

      pthread_detach(ntid);
      while( p_ctl->client_fd > 0 )
      {
        _ssid_info_scan(p_info,p_ctl->scan_key); 
        if(p_info->num > 0 )
        {
          if( _ssid_info_send( p_ctl->client_fd,p_info ) == STATE_SOCKET_FAIL )
          {
            _debug_info(1,"client fd %d send fail,will close  \n",p_ctl->client_fd );
            close(p_ctl->client_fd);
            p_ctl->client_fd = -1;
            break;
          }
        }
        sleep(p_ctl->scan_time);
        _debug_info(0,"sleep %d sec scan next\n",p_ctl->scan_time);
      } 
  }
 	pthread_attr_destroy(&thread_attr);
  return STATE_OK;
}



static  ctrl_info_t s_ctrl;
static  ssid_info_t s_ssid;
int  main()
{
  //_debug_init();
  _debug_info(1,"start\n");

  _ctrl_info_get( &s_ctrl );
  
  
  _socket_tcp_task( &s_ctrl ,&s_ssid );
  
  return 0;
}




