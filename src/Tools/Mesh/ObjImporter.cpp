//
// Created by Jury Verrigni on 3/29/17.
//

#include "ObjImporter.h"

MeshComponent *ObjImporter::CreateMeshFromFileName(const char *ObjFileName) {
    std::ifstream File(ObjFileName);
    std::string FileRow;
    std::string ShaderText;
    std::vector<float>* Points = new std::vector<float>;
    std::vector< std::vector<int> >* Faces = new std::vector< std::vector<int> >;
    std::vector<int> *RawFaces = new std::vector<int>;

    while (std::getline(File, FileRow)) {
        ParseLine(FileRow, Points, Faces, RawFaces);
    }

    if (!Points->empty() || !Faces->empty()) {
        MeshComponent* NewMesh = new MeshComponent;
        NewMesh->SetPoints(*Points);
        NewMesh->SetFaces(*Faces);
        NewMesh->SetRawFaces(*RawFaces);
        NewMesh->Optimise();
        return NewMesh;
    }

    return nullptr;
}

void ObjImporter::ParseLine(std::string Line, std::vector<float> *Points, std::vector< std::vector<int> > *Faces, std::vector<int> *RawFaces) {
    if (Line.empty()) {
        return;
    }
    switch (Line.at(0)) {
        //It's a comment, scratch that
        case '#':
        default:
            return;

        case 'g':
            //it's the mesh name
            break;

        case 'v':
            if (Line.at(1) == 'n') {
                // Normal map coord
            } else {
                // Verticles
                ParseVerticlesAtLine(Line, Points);
            }
            break;
        case 'f':
            // Faces
            ParseFacesAtLine(Line, Faces, RawFaces);
            break;
    }
}

void ObjImporter::ParseVerticlesAtLine(std::string Line, std::vector<float> *Points) {
    std::regex VerticlesRegex("((-|\\+)?\\d+\\.\\d+)+");
    std::smatch Matches;

    std::sregex_iterator NextMatch(Line.begin(), Line.end(), VerticlesRegex);
    std::sregex_iterator End;
    while (NextMatch != End) {
        std::smatch Match = *NextMatch;
        Points->push_back(std::stof(Match.str().c_str(), 0));
        NextMatch++;
    }
}

void ObjImporter::ParseFacesAtLine(std::string Line, std::vector< std::vector<int> > *Faces, std::vector<int> *RawFaces) {
    std::regex FacesRegex("(\\d+)+");
    std::smatch Matches;

    std::sregex_iterator NextMatch(Line.begin(), Line.end(), FacesRegex);
    std::sregex_iterator End;
	std::vector<int> LineFaces;
    while (NextMatch != End) {
        std::smatch Match = *NextMatch;
		LineFaces.push_back(std::stoi(Match.str().c_str(), 0) - 1);
        NextMatch++;
    }

	if (!LineFaces.empty()) {
		Faces->push_back(LineFaces);
	}
}
