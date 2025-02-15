#include "Precompiled.h"
#include "DrawStaticMeshCommand.h"
#include "Mesh/StaticMesh.h"
#include "Material/Material.h"
#include "Core/Core.h"
#include "System/RenderSystem.h"

FDrawStaticMeshCommand::FDrawStaticMeshCommand(FStaticMesh* InStaticMesh, const std::vector<FMaterial*>& InMaterials)
	: StaticMesh(InStaticMesh)
	, Materials(InMaterials)
{
}

void FDrawStaticMeshCommand::Execute()
{
	CCore::Get().GetRenderSystem()->DrawStaticMesh(StaticMesh, Materials);
}
