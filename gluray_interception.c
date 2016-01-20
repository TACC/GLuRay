#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>

#include "defines.h"

#include "NextDeclarations.h"
#include "function_map.c"


static void initializeInterception(void) __attribute__ ((__constructor__));

int is_initialized= 0;

static void initializeInterception(void)
{
  if(is_initialized)
    return;
  
    int i;
    for(i= 0; function_map[i].pointer!= NULL; i++)
      *(function_map[i].pointer)= dlsym(RTLD_NEXT, function_map[i].name);
    
    is_initialized= 1;
}

#include "enum_tables.c"

char *getEnumString(GLenum value)
{
  int i;
  for(i= 0; i< sizeof(enum_translations); i++)
    if(enum_translations[i].value== value)
      return enum_translations[i].name;
    
  return "Enum not found!";
}

void debugPrint(const char *format, ...)
{
#if DEBUG_GL
  va_list arguments;
  va_start (arguments, format);
  vfprintf (stderr, format, arguments);
  va_end (arguments);
#endif
}

void printGLError()
{
#if INTERCEPT_GL_ERRORS
  GLenum error= next_glGetError();
  while(error!= GL_NO_ERROR)
  {
    debugPrint("OpenGL Error: %s", getEnumString(error));
    error= glGetError();
  }
#endif
}

#include "intercepts.c"
#include "passthrough_intercepts.c"


