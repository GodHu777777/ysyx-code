#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  for(int i = 0; ; i++) {
    if(s[i] == '\0') return i;
  }
  panic("Not implemented");
}

char *strcpy(char *dst, const char *src) {
  int n = strlen(src);

  for(int i = 0; i <= n; i++) {
    dst[i] = src[i];
  }
  return dst;

  panic("Not implemented");
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  int n = strlen(src);
  int n1 = strlen(dst);
  for(int i = 0; i <= n; i++) {
    dst[n1 + i] = src[i];
  }

  return dst;
  panic("Not implemented");
}

int strcmp(const char *s1, const char *s2) {
  int n = (strlen(s1) > strlen(s2)) ? strlen(s1) : strlen(s2);
  
  for(int i = 0; i < n; i++) {
    if(s1[i] == s2[i]) continue;
    else return s1[i] - s2[i];
  }

  return 0;
  panic("Not implemented");
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {

  unsigned char* p = s;

  for(int i = 0; i < n; i++) {
    p[i] = (unsigned int)c;
  }

  return s;
  panic("Not implemented");
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  
  panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  unsigned char *p1 = (unsigned char *)s1, *p2 = (unsigned char *)s2;

  for(int i = 0; i < n; i++) {
    if(p1[i] == p2[i]) continue;
    else return p1[i] - p2[i];
  }
  
  return 0;
  panic("Not implemented");
}

#endif
