#include "obj_parser.ih"

void ObjParser::parseVertex(std::string const &line)
{
    std::stringstream str(line);
    std::string firstbit;
    str >> firstbit;
    float a;
    str >> a;
    float b;
    str >> b;
    float c;
    str >> c;
    //std::cout << '[' << a << ", " << b << ", " << c << "]\n";
    d_vertices.push_back(a);
    d_vertices.push_back(b);
    d_vertices.push_back(c);
}