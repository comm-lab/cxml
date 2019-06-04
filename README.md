# cxml

### Introduction
This is a simple XML pull parser written in C. Its features:

* Two file (*.h *.c) implementation
* No dynamic allocation
* No external dependency (not even libc)
* C99 standard

To use the library, just add the files _cxml.c_ and _cxml.h_ to your project.
If you need some type conversion functions (these rely on libc), include  also _cxml\_types.c_
and _cxml\_types.h_.

### Note
Warning! this library has been written to be used in embedded environment so while it is very simple and lightweight,
it may contain bugs.

### Usage example

```c
const char* XML = 
    "<Root>"
    "   <Item num='1'/>"
    "   <Item num='2'/>"
    "   <Child>Lorem ipsum</Child>"
    "</Root>";

struct XmlDocument doc;
xml_document_create(&doc, XML, strlen(XML));

int event;
while ((event = xml_read(&doc)) != XML_EOF) {
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
    
    case XML_TEXT: {
        struct XmlString text = xml_text(&doc);
        ...
        break;
    }

    default: break;
    }
}
```
