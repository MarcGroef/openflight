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
    void parseVertexNormalTextureIdcSquare(std::string const &line);
    void parseUV(std::string const &line);
    void handleFType(std::string const &line);
    void rollout();
    void setMaterial(std::string const &line);
};

inline ObjParser::ObjParser(std::string const &objfile)
{
    
    std::string mtlfile(objfile);
    mtlfile[mtlfile.size() - 1] = 'l';
    mtlfile[mtlfile.size() - 2] = 't';
    mtlfile[mtlfile.size() - 3] = 'm';
    
    d_objFolder = objfile;
    char c;
    for(c = d_objFolder[d_objFolder.size() - 1]; c != '/'; c = d_objFolder[d_objFolder.size() - 1])
        d_objFolder.resize(d_objFolder.size() - 1);
    
    d_mtlParser.parseMTL(mtlfile);
    
    d_activeObject.d_name = "";
    
    std::ifstream filestr;
    filestr.open(objfile.c_str(), std::ios::in);
    if(!filestr.good())
        std::cout << "error opening " << objfile << '\n';
    while(filestr.good())
    {
        std::string line;
        std::getline(filestr, line);
        parseLine(line);
    }
    rollout();
    d_activeObject.d_interleaved = std::move(d_interleaved);
    d_interleaved.clear();
    d_objects.push_back(d_activeObject);
    std::cout << "read " << d_objects.size() << " objects\n";
}

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
    std::cout << d_activeObject.d_name << " gets texture " << d_activeObject.d_material.d_map_Kd << '\n';
}

inline void ObjParser::parseObject(std::string const &line)
{

    
    if (d_activeObject.d_name != "")
    {
        //std::cout << d_activeObject.d_name << '\n';

        rollout();
        //std::cout << d_interleaved.size() << '\n';
        d_activeObject.d_interleaved = std::move(d_interleaved);
        //d_interleaved.clear();
        d_objects.push_back(d_activeObject);
        //std::cout << "pushed back " << d_activeObject.d_name << '\n';

    }
    std::stringstream str(line);
    std::string firstbit;
    str >> firstbit;
    str >> d_activeObject.d_name;  
    d_activeObject.d_material.d_map_Kd = "";
    //std::cout << "parsed " << d_activeObject.d_name << "at line " << line << '\n';
}

inline void ObjParser::rollout()
{
    std::vector<GLfloat> finalBuffer;
    //std::cout << d_vertIdc.size() << " vert Idc\n" ;
    for(size_t vIdx = 0; vIdx != d_vertIdc.size(); ++vIdx)
    {
        for(size_t idx = 0; idx != 3; ++idx)
            finalBuffer.push_back(d_vertices[(d_vertIdc[vIdx] - 1) * 3 + idx]);
        
        for(size_t idx = 0; idx != 3; ++idx)
            finalBuffer.push_back(d_normals[(d_normIdc[vIdx] - 1) * 3 + idx]);
        for(size_t idx = 0; idx != 2; ++idx)
            finalBuffer.push_back(d_uv[(d_textIdc[vIdx] - 1) * 2 + idx]);
        
    }
    //std::cout << "finalbuffersize = " << finalBuffer.size() << '\n';
    d_interleaved = std::move(finalBuffer);
    //d_normals = finalNormals;
    
    d_vertIdc.clear();
    d_normIdc.clear();
    d_textIdc.clear();
    //d_vertices.clear();
    //d_normals.clear();
    //d_uv.clear();
}


inline void ObjParser::parseVertexIdc(std::string const &line)
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


inline void ObjParser::parseVertex(std::string const &line)
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
    //std::cout << '[' << a << ", " << b << ", " << c << "]\n";
    d_vertices.push_back(a);
    d_vertices.push_back(b);
    d_vertices.push_back(c);
}

inline void ObjParser::parseUV(std::string const &line)
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

inline void ObjParser::parseVertexNormal(std::string const &line)
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

inline void ObjParser::parseVertexNormalIdc(std::string const &line)
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

inline void ObjParser::parseVertexTextureIdc(std::string const &line)
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
        d_vertIdc.push_back(a);
        d_textIdc.push_back(b);
    }
    //std::cout << d_normals.size() << '\n';
}

inline void ObjParser::parseVertexNormalTextureIdc(std::string const &line)
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

inline void ObjParser::parseVertexNormalTextureIdcSquare(std::string const &line)
{
    std::stringstream str(line);
    std::string firstbit;
    str >> firstbit;
    char slack;
    for(size_t idx = 0; idx != 4; ++idx)
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
        if(idx < 3)
        {
            d_vertIdc.push_back(a);
            d_normIdc.push_back(c);
            d_textIdc.push_back(b);
        } else
        {
            
            
            d_vertIdc.push_back(d_vertIdc[d_vertIdc.size() - 1]);
            d_normIdc.push_back(d_normIdc[d_normIdc.size() - 1]);
            d_textIdc.push_back(d_textIdc[d_textIdc.size() - 1]);
            
            d_vertIdc.push_back(a);
            d_normIdc.push_back(c);
            d_textIdc.push_back(b);
            
            d_vertIdc.push_back(d_vertIdc[d_vertIdc.size() - 5]);
            d_normIdc.push_back(d_normIdc[d_normIdc.size() - 5]);
            d_textIdc.push_back(d_textIdc[d_textIdc.size() - 5]);
            
            
            

        }
    }
    //std::cout << d_normals.size() << '\n';
}

inline void ObjParser::handleFType(std::string const &line)
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
            parseVertexNormalTextureIdcSquare(line);
        }
    }
    else
        parseVertexIdc(line);

}

inline void ObjParser::parseLine(std::string const &line)
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



#endif