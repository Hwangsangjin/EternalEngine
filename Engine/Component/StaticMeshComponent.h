#pragma once

#include "ActorComponent.h"

class FStaticMesh;
class FMaterial;

class ENGINE_API CStaticMeshComponent : public CActorComponent
{
	RTTI_DECL(CStaticMeshComponent, CActorComponent)

public:
	CStaticMeshComponent(CActor* InActor, const FString& InName);
	virtual ~CStaticMeshComponent() = default;

	virtual void Render() override;

	FORCEINLINE FStaticMesh* GetStaticMesh() const { return StaticMesh; }
	FORCEINLINE void SetStaticMesh(FStaticMesh* InStaticMesh) { StaticMesh = InStaticMesh; }

	FORCEINLINE FMaterial* GetMaterial(size_t Index) const { return Index < Materials.size() ? Materials[Index] : nullptr; }
	FORCEINLINE const std::vector<FMaterial*>& GetMaterials() const { return Materials; }
	FORCEINLINE void SetMaterial(size_t Index, FMaterial* InMaterial)
	{
		if (Index >= Materials.size())
			Materials.resize(Index + 1, nullptr);

		Materials[Index] = InMaterial;
	}

private:
	FStaticMesh* StaticMesh;
	std::vector<FMaterial*> Materials;
};
