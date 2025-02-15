#include "Precompiled.h"
#include "StaticMeshComponent.h"
#include "Mesh/StaticMesh.h"
#include "Material/Material.h"
#include "Command/DrawStaticMeshCommand.h"
#include "Core/Core.h"
#include "System/RenderSystem.h"

CStaticMeshComponent::CStaticMeshComponent(CActor* InActor, const FString& InName)
	: Super(InActor, InName)
    , StaticMesh(nullptr)
{
}

void CStaticMeshComponent::Render()
{
    if (!StaticMesh || Materials.empty())
        return;

    FDrawStaticMeshCommand* DrawStaticMeshCommand = new FDrawStaticMeshCommand(StaticMesh, Materials);
    CCore::Get().GetRenderSystem()->EnqueueCommand(DrawStaticMeshCommand);
}
