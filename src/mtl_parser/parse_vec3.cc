#include "mtl_parser.ih"

glm::vec3 MTLParser::parseVec3(std::stringstream &str)
{
    glm::vec3 vec;
    float num;
    str >> num;
    vec[0] = num;
    str >> num;
    vec[1] = num;
    str >> num;
    vec[2] = num;
    return vec;
}