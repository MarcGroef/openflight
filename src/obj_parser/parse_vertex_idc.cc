#include "obj_parser.ih"

void ObjParser::parseVertexIdc(std::string const &line)
{
    std::stringstream str(line);
    std::string firstbit;
    str >> firstbit;
    int a;
    str >> a;
    int b;
    str >> b;
    int c;
    str >> c;
    //std::cout << '[' << a << ", " << b << ", " << c << "]\n";
    d_vertIdc.push_back(a);
    d_vertIdc.push_back(b);
    d_vertIdc.push_back(c);
}
