#include "obj_parser.ih"

void ObjParser::parseLine(std::string const &line)
{
    char c = line[0];
    switch(c)
    {
        case 'v':
            //std::cout << line << '\n';
            if(line[1] == 'n')
                parseVertexNormal(line);
            else if(line[1] == 't')
                parseUV(line);
            else                
                parseVertex(line);
            break;
        case 'f':
                handleFType(line);
            break;
        case 's':
            break;
        case 'u':
            setMaterial(line);
            break;
        case 'o':
            parseObject(line);
            break;
        case '#':
        default:
            std::cout << "skipped " << line << '\n';
            break;
    }
}