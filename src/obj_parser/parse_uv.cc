#include "obj_parser.ih"

void ObjParser::parseUV(std::string const &line)
{
    std::stringstream str(line);
    std::string firstbit;
    str >> firstbit;
    float a;
    str >> a;
    float b;
    str >> b;
    //std::cout << '[' << a << ", " << b << "]\n";
    d_uv.push_back(a);
    d_uv.push_back(b);
    
}
