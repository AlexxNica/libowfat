#include "fmt.h"
#include "textcode.h"
#include "str.h"
#include "haveinline.h"

static inline int tohex(char c) {
  return c>9?c-10+'A':c+'0';
}

unsigned int fmt_urlencoded(char* dest,const char* src,unsigned int len) {
  const char unsafe[]=" %<>\"#{}|\\^~[]`;/?:@=&";
  register const unsigned char* s=(const unsigned char*) src;
  unsigned long written=0,i;
  for (i=0; i<len; ++i) {
    if (s[i]&0x80 || unsafe[str_chr(unsafe,s[i])]==s[i]) {
      if (dest) {
	dest[written]='%';
	dest[written+1]=tohex(s[i]>>4);
	dest[written+2]=tohex(s[i]&15);
      }
      written+=3;
    } else {
      if (dest) dest[written]=s[i]; ++written;
    }
  }
  return written;
}