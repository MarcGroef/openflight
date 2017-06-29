#include "obj_parser.ih"

void ObjParser::parseVertexNormalIdc(std::string const &line)
{
    std::stringstream str(line);
    std::string firstbit;
    str >> firstbit;
    char slack;
    for(size_t idx = 0; idx != 3; ++idx)
    {
        int a;
        str >> a;
        str >> slack;
        str >> slack;
        int b;
        str >> b;        
        d_vertIdc.push_back(a);
        d_normIdc.push_back(b);
    }
    //std::cout << d_normals.size() << '\n';
}