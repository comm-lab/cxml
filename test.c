#include <stdio.h>
#include "cxml.h"
#include "cxml_types.h"
#include <stdlib.h>

int main (int argc, char** argv) {
    char* file = malloc(2048);

    FILE* fp = fopen("test.xml", "rb");
    long size = fread(file, 1, 2048, fp);
    fclose(fp);

    struct XmlDocument doc; 
    xml_document_create(&doc, file, size);

    const char* indent = 
    "                                  "
    "                                  "
    "                                  "
    "                                  "
    "                                  "
    "                                  "
    "                                  "
    "                                  "
    "                                  "
    "                                  "
    "                                  "
    "                                  "
    "                                  "
    "                                  ";
    int idt = 0;

    int evt = XML_EOF;
    while((evt = xml_read(&doc)) != XML_EOF) {
        switch(evt) {
            case XML_TAG_BEGIN:{
                struct XmlString str = xml_name(&doc);
                printf("%.*stag %.*s\n", idt, indent, str.length, str.str);
                idt+=2;
                break;
            }

            case XML_TEXT: {
                struct XmlString str = xml_text(&doc);
                xml_string_trim(&str);
                if(str.length > 0)
                    printf("%.*stext %.*s\n", idt, indent, str.length, str.str);
                break;
            }

            case XML_ATTRIBUTE: {
                struct XmlString attr_name = xml_attr_name(&doc);
                struct XmlString attr_val = xml_attr_value(&doc);
                printf("%.*sattr %.*s = %.*s\n", idt, indent, 
                    attr_name.length, attr_name.str,
                    attr_val.length, attr_val.str);
                break;
            }

            case XML_TAG_END: {
                idt-=2;
                break;
            }
            
        }
    }

    free(file);
    return 0;
}