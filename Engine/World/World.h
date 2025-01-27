#pragma once

class CLevel;

class CWorld
{
public:
	CWorld();
	~CWorld();

	void Update(float DeltaTime);
	void Render();

	void LoadLevel(CLevel* InLevel);

	FORCEINLINE CLevel* GetPersistentLevel() const { return PersistentLevel; }
	FORCEINLINE void SetPersistentLevel(CLevel* InLevel) { PersistentLevel = InLevel; }

private:
	CLevel* PersistentLevel;
};
