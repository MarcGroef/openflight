#ifndef INCLUDED_OBJ_PARSER_H_
#define INCLUDED_OBJ_PARSER_H_

#include <string>
#include <GL/gl.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

class ObjParser
{
public:
    std::vector<GLfloat> d_vertices;
    std::vector<GLuint> d_vertIdc;
    std::vector<GLfloat> d_uv;
    std::vector<GLfloat> d_normals;
    std::vector<GLuint> d_normIdc;
    std::vector<GLuint> d_textIdc;
    
    ObjParser(std::string const &objfile);
private:
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
};


inline void ObjParser::rollout()
{
    std::vector<GLfloat> finalBuffer;
    
    for(size_t vIdx = 0; vIdx != d_vertIdc.size(); ++vIdx)
    {
        for(size_t idx = 0; idx != 3; ++idx)
            finalBuffer.push_back(d_vertices[(d_vertIdc[vIdx] - 1) * 3 + idx]);
        
        for(size_t idx = 0; idx != 3; ++idx)
            finalBuffer.push_back(d_normals[(d_normIdc[vIdx] - 1) * 3 + idx]);
        for(size_t idx = 0; idx != 2; ++idx)
            finalBuffer.push_back(d_uv[(d_textIdc[vIdx] - 1) * 2 + idx]);
        
    }
    d_vertices = finalBuffer;
    //d_normals = finalNormals;
    d_vertIdc.clear();
    d_normIdc.clear();
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

inline void ObjParser::handleFType(std::string const &line)
{
    if(line.find("//") != std::string::npos)
        parseVertexNormalIdc(line);
    else if(line.find("/") != std::string::npos)
    {
        size_t n = std::count(line.begin(), line.end(), '/');
        if (n == 3 )
        {
            parseVertexTextureIdc(line);
        }else if(n == 6)
        {
            parseVertexNormalTextureIdc(line);
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
        case 'o':
        case '#':
        default:
            break;
    }
}

inline ObjParser::ObjParser(std::string const &objfile)
{
    std::ifstream filestr;
    filestr.open(objfile.c_str(), std::ios::in);
    while(filestr.good())
    {
        std::string line;
        std::getline(filestr, line);
        parseLine(line);
    }
    rollout();
}

#endif