#pragma once

#include "Actor.h"

class ENGINE_API CPrompter : public CActor
{
	RTTI_DECL(CPrompter, CActor)

public:
	CPrompter(char Image = ' ');
	virtual ~CPrompter();

	virtual void Render() override;
	virtual void SetPosition(const FVector2& NewPosition) override;

private:
	// 화면에 그릴 문자 값
	char Image;
};
