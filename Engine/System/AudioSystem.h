#pragma once

namespace FMOD
{
	class System;
	class Sound;
	class Channel;
};

class ENGINE_API CAudioSystem
{
public:
	CAudioSystem();
	~CAudioSystem();

	FString GetResourcePath(const FString& FileName);

	void CreateSound(const FString& FileName, const FString& SoundName, bool bLoop = false);

	void PlayBackgroundMusic(const FString& SoundName);
	void StopBackgroundMusic(const FString& SoundName);

#undef PlaySound
	void PlaySound(const FString& SoundName);
	void StopSound(const FString& SoundName);
	void PauseSound(const FString& SoundName);
	void ResumeSound(const FString& SoundName);
	void SetVolume(const FString& SoundName, float Volume);
	void SetPitch(const FString& SoundName, float Pitch);
	void SetPan(const FString& SoundName, float Pan);

	bool IsPlaying(const FString& SoundName);

private:
	// FMOD 시스템 객체
	FMOD::System* System;

	// 사운드 객체를 저장하는 맵
	std::map<FString, FMOD::Sound*> Sounds;

	// 사운드 채널 객체를 저장하는 맵
	std::map<FString, FMOD::Channel*> Channels;
};
