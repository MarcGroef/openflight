#include "obj_parser.ih"

void ObjParser::setMaterial(std::string const &line)
{
    std::stringstream str(line);
    std::string s;
    str >> s;
    str >> s;
    d_activeObject.d_material = d_mtlParser.get(s);
    if (d_activeObject.d_material.d_map_Kd != "")
        d_activeObject.d_material.d_map_Kd = d_objFolder + d_activeObject.d_material.d_map_Kd;
}