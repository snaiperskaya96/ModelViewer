//
// Created by Jury Verrigni on 3/29/17.
//

#ifndef MODELVIEWER_OBJIMPORTER_H
#define MODELVIEWER_OBJIMPORTER_H


#include <Components/MeshComponent.h>
#include <fstream>
#include <vector>
#include <regex>
#include <iostream>

class ObjImporter {
public:
    static MeshComponent* CreateMeshFromFileName(const char* ObjFileName);
private:
    static void ParseLine(std::string Line, std::vector<float> *Points, std::vector< std::vector<int> > *Faces, std::vector<int> *RawFaces);

    static void ParseVerticlesAtLine(std::string Line, std::vector<float> *Points);

    static void ParseFacesAtLine(std::string Line, std::vector< std::vector<int> > *Faces, std::vector<int> *RawFaces);
};


#endif //MODELVIEWER_OBJIMPORTER_H
