#pragma once
// Minimal GL type definitions, kept self-contained so this project never
// includes the system <GL/gl.h> (whose dllimport function declarations
// would collide with the ones we generate for export/import here).

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef int GLint;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef char GLchar;
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned short GLushort;
typedef unsigned char GLubyte;
typedef unsigned long long GLuint64;
typedef struct __GLsync* GLsync;

#if defined(_WIN64)
typedef long long GLsizeiptr;
typedef long long GLintptr;
#else
typedef long GLsizeiptr;
typedef long GLintptr;
#endif

#ifdef _WIN32
#ifndef _WINGDI_
typedef void* HDC;
typedef void* HGLRC;
typedef int BOOL;
typedef unsigned int UINT;
#endif
#endif

#ifndef APIENTRY
#ifdef _WIN32
#define APIENTRY __stdcall
#else
#define APIENTRY
#endif
#endif

#ifndef WINGDIAPI
#ifdef _WIN32
#define WINGDIAPI
#endif
#endif
