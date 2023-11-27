#ifndef PKGL_BACKEND_H
#define PKGL_BACKEND_H

#include <stdint.h>
#include <stdlib.h>

#ifdef _WIN32
	#ifdef BUILD_LIBTYPE_SHARED
		#define RKGL_API __declspec(dllexport)
	#else
		#ifdef USE_LIBTYPE_SHARED
			#define RKGL_API __declspec(dllimport)
		#endif
	#endif
#endif

#ifndef RKGL_API
	#define RKGL_API
#endif

#ifndef PKGL_MALLOC
	#define PKGL_MALLOC(size) malloc(size)
#endif

#ifndef PKGL_CALLOC
	#define PKGL_CALLOC(num, size) calloc(nun, size)
#endif

#ifndef PKGL_REALLOC
	#ifndef PKGL_DROP_SAFE_REALLOC
		#define PKGL_REALLOC(ptr, size) pkgl_safe_realloc(ptr, size)
	#else
		#define PKGL_REALLOC(ptr, size) realloc(ptr, size)
	#endif
#endif

#ifndef PKGL_FREE
	#define PKGL_FREE(ptr) free(ptr)
#endif

// If realloc fails, ptr is not freed: possible mem leak. safe realloc fixes this problem
void* pkgl_safe_realloc(void* ptr, size_t size);

#ifdef PKGL_IMPLEMENTION
#ifndef PKGL_DROP_SAFE_REALLOC

void* pkgl_safe_realloc(void* ptr, size_t size)
{
	void* temp = realloc(ptr, size);
	
	if (temp == NULL)
	{
		PKGL_FREE(ptr);
	}
	
	return temp;
}

#endif //PKGL_DROP_SAFE_REALLOC
#endif //PKGL_IMPLEMENTION
#endif //PKGL_BACKEND_H