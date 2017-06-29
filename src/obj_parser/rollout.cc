#include "obj_parser.ih"

void ObjParser::rollout()
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