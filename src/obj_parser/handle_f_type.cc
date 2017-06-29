#include "obj_parser.ih"

void ObjParser::handleFType(std::string const &line)
{
    if(line.find("//") != std::string::npos)
        parseVertexNormalIdc(line);
    else if(line.find("/") != std::string::npos)
    {
        size_t n = std::count(line.begin(), line.end(), '/');
        if (n == 3 || n == 5)
        {
            parseVertexTextureIdc(line);
        }else if(n == 6 || n == 8)
        {
            parseVertexNormalTextureIdc(line);
        }else if (n == 8)
        {
            std::cout << "Unsupported obj format: Please use only triangles\n";//
        }
    }
    else
        parseVertexIdc(line);

}