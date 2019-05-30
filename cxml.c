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
int xml_string_cmp(struct XmlString* a, struct XmlString* b);

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include "cxml.h"


static int is_whitespace(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

void xml_document_create (struct XmlDocument* doc, 
                        const char* source, 
                        unsigned long length) 
{
    doc->source = source;
    doc->length = length;
    doc->cursor = 0;
    doc->internal_state = XML_IDLE;
}

int xml_read(struct XmlDocument* doc) {
    int event = XML_EOF;

    while(doc->cursor < doc->length) {
        switch(doc->source[doc->cursor]) {
            case ' ':
            case '\n':
            case '\r':
            case '\t':
                // Skip whitespace
                break;

            case '<':
                if(doc->source[doc->cursor + 1] != '/') {
                    event = XML_TAG_BEGIN;
                } else {
                    doc->cursor++;
                    event = XML_TAG_END;
                }
                goto on_event;
                break;

            case '>':
                if(doc->internal_state == XML_TAG_BEGIN) {
                    event = XML_TEXT;
                    goto on_event;
                } else {
                    event = XML_IDLE;
                }
                break;

            case '=':
                if(doc->internal_state == XML_TAG_BEGIN) {
                    doc->internal_state = XML_ATTRIBUTE;
                    return XML_ATTRIBUTE;
                } else if(doc->internal_state == XML_ATTRIBUTE) {
                    doc->internal_state = XML_TAG_BEGIN;
                }
                break;

            default:
                break;
        }

        doc->cursor++;
    }

on_event:
    doc->internal_state = event;
    return event;
}

struct XmlString xml_name(struct XmlDocument* doc) {
    struct XmlString str;
    str.str = &doc->source[++doc->cursor];
    str.length = 0;
    
    while(!is_whitespace(doc->source[doc->cursor]) &&
        doc->source[doc->cursor] != '>' &&
        doc->source[doc->cursor] != '/' &&
        doc->cursor < doc->length)
    {
        doc->cursor++;
        str.length++;
    }
    
    return str;
}

struct XmlString xml_text(struct XmlDocument* doc) {
    struct XmlString str;
    str.str = &doc->source[++doc->cursor];
    str.length = 0;
    
    while(doc->source[doc->cursor] != '<' &&
        doc->cursor < doc->length)
    {
        doc->cursor++;
        str.length++;
    }
    
    return str;
}

void xml_string_trim(struct XmlString* str) {
    while(is_whitespace(str->str[0]) && str->length) {
        str->str++;
        str->length--;
    }

    while(is_whitespace(str->str[str->length - 1]) && str->length) {
        str->length--;
    }
}


struct XmlString xml_attr_name(struct XmlDocument* doc) {
    struct XmlString str;
    str.str = &doc->source[doc->cursor]; // Cursor is placed at = character
    str.length = 0;
    
    while(*(str.str - 1) != ' ') {
        str.str--;
        str.length++;
    }

    return str;
}

struct XmlString xml_attr_value(struct XmlDocument* doc) {
    struct XmlString str;
    str.str = &doc->source[doc->cursor + 2]; // Cursor is placed at = character
    str.length = 0;
    
    while(str.str[str.length] != '"' && str.str[str.length] != '\'') {
        str.length++;
    }

    return str;
}

int xml_string_eq(struct XmlString* a, struct XmlString* b) {
    if(b->length != a->length) {
        return 0;
    }

    if(a->str == b->str) {
        // Both string refer to the same slice
        return 1;
    }

    for (long i=0; i < a->length; i++) {
        if(a->str[i] != b->str[i]) {
            return 0;
        }
    }

    return 1;
}

int xml_string_match(struct XmlString* a, const char* b) {
    for(long i=0; i<a->length; i++) {
        if(a->str[i] != b[i] || b[i] == 0) {
            return 0;
        }
    }

    return 1;
}