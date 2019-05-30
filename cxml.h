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
    This is a simple, zero allocation, zero dependencies XML pull parser. It works by scanning the document
    and returning XmlEvent whenever it encounters an XML element. It is up to the user
    to retrieve the values and manage the memory to store them.
*/


struct XmlDocument {
    const char* source;
    unsigned long length;
    long cursor;
    int internal_state;
};

struct XmlString {
    const char* str;
    unsigned long length;
};

enum XmlEvent {
    XML_IDLE,
    XML_EOF,
    XML_TAG_BEGIN,
    XML_TAG_END,
    XML_TEXT,
    XML_ATTRIBUTE,
};

// Initializes the document with the provided XML source
void xml_document_create (struct XmlDocument* doc, 
                        const char* source, 
                        unsigned long length);
// Each call to xml_read() advances the parser and returns an
// XmlEvent whenever it encounters a tag/attribute/text/eof 
int xml_read (struct XmlDocument* doc);
// Returns current tag name
struct XmlString xml_name(struct XmlDocument* doc);
// Returns current text content
struct XmlString xml_text(struct XmlDocument* doc);
// Returns current attribute name
struct XmlString xml_attr_name(struct XmlDocument* doc);
// Returns current attribute value
struct XmlString xml_attr_value(struct XmlDocument* doc);
// Removes whitespace from beginning and end of a string
void xml_string_trim(struct XmlString* str);
// Returns 1 when the strings are equal, 0 otherwise
int xml_string_eq(struct XmlString* a, struct XmlString* b);
