#include "obj_parser.ih"

void ObjParser::parseVertexNormalTextureIdc(std::string const &line)
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
        int b;
        str >> b;
        str >> slack;
        int c;
        str >> c;
    // std::cout << "n:[" << a << ", " << b << ", " << c << "]\n";
        d_vertIdc.push_back(a);
        d_normIdc.push_back(c);
        d_textIdc.push_back(b);
    }
    //std::cout << d_normals.size() << '\n';
}