# cxml

### Introduction
This is a simple XML pull parser written in C. Its features:

* Two file (*.h *.c) implementation
* No dynamic allocation
* No external dependency (even libc)
* C99 standard

To use the library, just add the files _cxml.c_ and _cxml.h_ to your project.
If you need some type conversion functions (these rely on libc), include  also _cxml\_types.c_
and _cxml\_types.h_.

### Usage example

```c
const char* XML = 
    "<Root>"
    "   <Item num='1'/>"
    "   <Item num='2'/>"
    "</Root>";

struct XmlDocument doc;
xml_document_create(&doc, XML, strlen(XML));

int event;
while ((event = xml_read(&doc))) {
    switch (event)
    {
    case XML_TAG_BEGIN: {
        struct XmlString name = xml_name(&doc);
        ...
        break;
    }

    case XML_ATTRIBUTE: {
        struct XmlString name = xml_attr_name(&doc);
        struct XmlString value = xml_attr_value(&doc);
        ...
        break;
    }

    default: break;
    }
}
```