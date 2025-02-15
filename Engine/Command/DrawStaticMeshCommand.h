#pragma once

#include "DrawCommand.h"

class FStaticMesh;
class FMaterial;

class ENGINE_API FDrawStaticMeshCommand : public FDrawCommand
{
public:
    FDrawStaticMeshCommand(FStaticMesh* InStaticMesh, const std::vector<FMaterial*>& InMaterials);
    virtual ~FDrawStaticMeshCommand() = default;

    virtual void Execute();

private:
    FStaticMesh* StaticMesh;
    std::vector<FMaterial*> Materials;
};
