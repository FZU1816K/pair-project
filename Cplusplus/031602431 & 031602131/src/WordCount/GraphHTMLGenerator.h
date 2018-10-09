#ifndef GRAPH_HTML_GENERATOR_H
#define GRAPH_HTML_GENERATOR_H

#include "Status.h"

class GraphHTMLGenerator
{
public:
    GraphHTMLGenerator();
    GraphHTMLGenerator(Status* status);
    ~GraphHTMLGenerator();

    string fileName;
};

#endif