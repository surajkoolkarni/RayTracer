#include "Vertex.h"


Vertex::Vertex(const aiVector3D& pos, const aiVector3D& normal, const aiVector2D& texcoords) :
	Position(pos), Normal(normal), TexCoords(texcoords)
{
}
