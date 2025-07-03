#include "log.h"
#include <string.h>
#include <time.h>
static FILE *s_debug_fp = NULL;

int _cur_time_string_get( char *p_time )
{
  time_t current_time = time(NULL);
  struct tm *tm       = NULL;
  
  tm = localtime(&current_time);
  sprintf(p_time,"%04d-%02d-%02d %02d:%02d:%02d ",tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, 
    (tm->tm_hour)%24, tm->tm_min, tm->tm_sec);
  return 0;
  
}

int lpm_info(int save,char *msg,...)
{
  va_list argp;
  va_start( argp, msg );
  char *p_start = NULL;
  char tmp_val[LOG_MAX_LEN] = {0};
  _cur_time_string_get(tmp_val);
  
  
  p_start = tmp_val + strlen(tmp_val);
  vsnprintf(p_start,LOG_MAX_LEN - strlen(tmp_val), msg,argp);
  printf("%s",tmp_val);
  va_end(argp);
  
  if( save )
  {
    s_debug_fp = fopen("/home/xhh/log/update.log","at+");
    fprintf(s_debug_fp,"%s",tmp_val );
    fclose(s_debug_fp);
  }
  return 0;
}

