#ifndef INCLUDED_OBJ_PARSER_H_
#define INCLUDED_OBJ_PARSER_H_

#include <string>
#include <GL/gl.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "../mtl_parser/mtl_parser.h"


struct object
{
    std::vector<GLfloat> d_interleaved;
    std::string d_name;
    material d_material;
};

class ObjParser
{
    
    std::vector<GLuint> d_vertIdc;
    std::vector<GLfloat> d_uv;
    std::vector<GLfloat> d_normals;
    std::vector<GLuint> d_normIdc;
    std::vector<GLuint> d_textIdc;
    std::vector<GLfloat> d_vertices;
    object d_activeObject;
    std::string d_objFolder;
public:
    
    std::vector<GLfloat> d_interleaved;
    std::vector<object> d_objects;


    
    MTLParser d_mtlParser;
    
    ObjParser(std::string const &objfile);
private:
    void parseObject(std::string const &line);
    void parseLine(std::string const &line);
    void parseVertex(std::string const &line);
    void parseVertexNormal(std::string const &line);
    void parseVertexNormalTextureIdc(std::string const &line);
    void parseVertexTextureIdc(std::string const &line);
    void parseVertexNormalIdc(std::string const &line);
    void parseVertexIdc(std::string const &line);
    void parseUV(std::string const &line);
    void handleFType(std::string const &line);
    void rollout();
    void setMaterial(std::string const &line);
};



inline void ObjParser::setMaterial(std::string const &line)
{
    std::stringstream str(line);
    std::string s;
    str >> s;
    str >> s;
    //std::cout << "searching material " << s << '\n';
    d_activeObject.d_material = d_mtlParser.get(s);
    if (d_activeObject.d_material.d_map_Kd != "")
        d_activeObject.d_material.d_map_Kd = d_objFolder + d_activeObject.d_material.d_map_Kd;
    //std::cout << d_activeObject.d_name << " gets texture " << d_activeObject.d_material.d_map_Kd << '\n';
}
#endif