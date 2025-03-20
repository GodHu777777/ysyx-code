#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);

  int n = strlen(fmt);

  int cnt = 0;

  // i is in fmt
  // start from 1 to ignore "" (Fixed: well, ""doesn't matter, so i start from 0)
  for(int i = 0; i < n; i++) {
    if(fmt[i] != '%') {
      out[cnt++] = fmt[i];
    }else {
      // match format
      if(fmt[i + 1] == 'd') {
        // get data from argument list
        int value = va_arg(args, int);
        char rev_str_value[128] = "";
        char str_value[128] = "";

        int sum = 0;

        // assert(value == 12);

        int tmp = value;
        while(tmp > 0) {
          // printf("# DEBUG: %d", tmp);

          rev_str_value[sum++] = (tmp % 10) + 0x30;
          tmp /= 10;
        }
      
        rev_str_value[sum] = '\0';

        // assert(rev_str_value[0] == '1');
        
        for(int i = 0; i < sum; i++) {
          str_value[i] = rev_str_value[sum - i - 1];
        }
        
        str_value[sum] = '\0';

        strcat(out, str_value);
        cnt += strlen(str_value);
        i++;
      }else if(fmt[i + 1] == 's') {
        // get data from argument list
        char* cur_str = va_arg(args, char *);

        strcat(out, cur_str);
        cnt += strlen(cur_str);
        i++;
      }
    }
  }

  return cnt;
  
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
