#pragma once

// ������Ʈ Ŭ����
class CObject
{
public:
	CObject();
	virtual ~CObject();

	// ���� ó�� �Լ�
	virtual void Update(float DeltaTime);
	virtual void Render();

protected:
	// Ȱ��ȭ �������� ��Ÿ���� ����
	bool bActive;

	// ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool bExpired;
};

