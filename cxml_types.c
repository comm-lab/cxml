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

#include <cxml_types.h>
#include <stdlib.h>

/*
    To make the XmlString look like a c-string, 
    I take a copy of the first character after the string,
    set the original to null and then restore it afterwards.
    This will avoid unwanted allocations/copies.
    WARNING: the text buffer to which the XmlString refers should be
    1 byte longer than its content to avoid segmentation faults
*/

unsigned char xml_to_uint8(struct XmlString* str) {
    return (unsigned char) xml_to_uint64(str);
}

unsigned short xml_to_uint16(struct XmlString* str) {
    return (unsigned short) xml_to_uint64(str);
}

unsigned int xml_to_uint32(struct XmlString* str) {
    return (unsigned int) xml_to_uint64(str);
}

unsigned long xml_to_uint64(struct XmlString* str) {
    char temp = str->str[str->length];
    ((char*)str->str)[str->length] = 0;
    unsigned long ret = (unsigned long) strtoul(str->str, NULL, 10);
    ((char*)str->str)[str->length] = temp;
    return ret;
}

char xml_to_int8(struct XmlString* str) {
    return (char) xml_to_int64(str);
}

short xml_to_int16(struct XmlString* str) {
    return (short) xml_to_int64(str);
}

int xml_to_int32(struct XmlString* str) {
    return (int) xml_to_int64(str);
}

long xml_to_int64(struct XmlString* str) {
    char temp = str->str[str->length];
    ((char*)str->str)[str->length] = 0;
    long ret = (long) strtol(str->str, NULL, 10);
    ((char*)str->str)[str->length] = temp;
    return ret;
}

float xml_to_float(struct XmlString* str) {
    char temp = str->str[str->length];
    ((char*)str->str)[str->length] = 0;
    float ret = (float) strtof(str->str, NULL);
    ((char*)str->str)[str->length] = temp;
    return ret;
}

double xml_to_double(struct XmlString* str) {
    char temp = str->str[str->length];
    ((char*)str->str)[str->length] = 0;
    double ret = (double) strtod(str->str, NULL);
    ((char*)str->str)[str->length] = temp;
    return ret;
}

char* xml_to_cstring(const struct XmlString* src) {
    char* cstr = malloc(src->length + 1);
    for(long i=0; i<src->length; i++) {
        cstr[i] = src->str[i];
    }
    cstr[src->length] = 0;
    return cstr;
}