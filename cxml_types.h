#pragma once

/*
MIT license

Copyright (c) 2019 comm-lab

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

/*
    Utility methods to convert XmlString into basic types
*/

#include <cxml.h>

// Unsigned integers
unsigned char xml_to_uint8(struct XmlString* str);
unsigned short xml_to_uint16(struct XmlString* str);
unsigned int xml_to_uint32(struct XmlString* str);
unsigned long xml_to_uint64(struct XmlString* str);
// Signed integers
char xml_to_int8(struct XmlString* str);
short xml_to_int16(struct XmlString* str);
int xml_to_int32(struct XmlString* str);
long xml_to_int64(struct XmlString* str);
// Floating point
float xml_to_float(struct XmlString* str);
double xml_to_double(struct XmlString* str);
// c-string (null terminated string)
// WARNING: returns a dynamically allocated string n+1 bytes long,
// so the user must free() it when done
char* xml_to_cstring(const struct XmlString* src);