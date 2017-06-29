#include "obj_parser.ih"

void ObjParser::parseVertexNormal(std::string const &line)
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
   // std::cout << "n:[" << a << ", " << b << ", " << c << "]\n";
    d_normals.push_back(a);
    d_normals.push_back(b);
    d_normals.push_back(c);
    //std::cout << d_normals.size() << '\n';
}