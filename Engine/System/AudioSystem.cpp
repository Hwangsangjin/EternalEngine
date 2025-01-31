#include "Precompiled.h"
#include "AudioSystem.h"
#include "FMOD/fmod.hpp"

CAudioSystem::CAudioSystem()
    : System(nullptr)
{
    // FMOD 시스템 객체 생성
    FMOD::System_Create(&System);

    // FMOD 시스템 초기화
    System->init(32, FMOD_INIT_NORMAL, nullptr);
}

CAudioSystem::~CAudioSystem()
{
    // 맵에 있는 모든 사운드를 해제
    for (const auto& Pair : Sounds)
        Pair.second->release();

    // FMOD 시스템 종료
    System->close();

    // FMOD 시스템 객체 해제
    System->release();
}

FString CAudioSystem::GetResourcePath(const FString& FileName)
{
    // 현재 실행 파일 경로
    std::filesystem::path CurrentPath = std::filesystem::current_path();

    // 상위 경로로 올라가면서 리소스 폴더 찾기
    while (CurrentPath.has_parent_path())
    {
        // 현재 경로를 상위 경로로 변경
        CurrentPath = CurrentPath.parent_path();

        // 리소스 폴더를 찾았다면 경로 결합 후 반환
        if (std::filesystem::exists(CurrentPath / "Resource"))
            return FString(CurrentPath.wstring().c_str()) + TEXT("/Resource/Sound/") + FileName;
    }

    // 리소스 폴더를 찾지 못한 경우 빈 문자열 반환
    return FString();
}

void CAudioSystem::CreateSound(const FString& FileName, const FString& SoundName, bool bLoop)
{
    // 이미 해당 이름의 사운드가 존재하면 생성하지 않음
    if (Sounds.find(SoundName) != Sounds.end())
        return;

    // 사운드 파일 경로 가져오기
    FString SoundPath = GetResourcePath(FileName);

    // 새로운 FMOD 사운드 객체 생성
    FMOD::Sound* NewSound = nullptr;
    System->createSound(SoundPath.ToString().c_str(), bLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF, nullptr, &NewSound);

    // 생성된 사운드 저장
    Sounds[SoundName] = NewSound;
}

void CAudioSystem::PlayBackgroundMusic(const FString& SoundName)
{
    // 이미 배경 음악이 재생 중인 경우 재생하지 않음
    if (IsPlaying(SoundName))
        return;

    // 배경 음악 재생
    PlaySound(SoundName);
}

void CAudioSystem::StopBackgroundMusic(const FString& SoundName)
{
    // 배경 음악 정지
    StopSound(SoundName);
}

void CAudioSystem::PlaySound(const FString& SoundName)
{
    // 저장된 사운드 찾기
    auto Iter = Sounds.find(SoundName);

    // 사운드를 찾을 수 없는 경우
    if (Iter == Sounds.end())
        return;

    // 사운드 가져오기
    FMOD::Sound* SoundPtr = Iter->second;

    // 새로운 채널을 생성하여 사운드 재생
    FMOD::Channel* NewChannel = nullptr;
    System->playSound(SoundPtr, nullptr, false, &NewChannel);

    // 재생 중인 채널 저장
    Channels[SoundName] = NewChannel;
}

void CAudioSystem::StopSound(const FString& SoundName)
{
    // 채널에서 사운드 찾기
    auto Iter = Channels.find(SoundName);

    // 채널을 찾을 수 없는 경우
    if (Iter == Channels.end())
        return;

    // 해당 사운드의 채널 가져오기
    FMOD::Channel* Channel = Iter->second;

    // 채널이 재생 중인지 확인
    bool bPlaying = false;
    Channel->isPlaying(&bPlaying);

    // 재생 중이면 정지
    if (bPlaying)
        Channel->stop();

    // 정지된 채널 정보 삭제
    Channels.erase(Iter);
}

void CAudioSystem::PauseSound(const FString& SoundName)
{
    // 채널에서 사운드 찾기
    auto Iter = Channels.find(SoundName);

    // 채널을 찾을 수 없는 경우
    if (Iter == Channels.end())
        return;

    // 해당 사운드의 채널 가져오기
    FMOD::Channel* Channel = Iter->second;

    // 채널이 재생 중이면 일시 정지
    bool bPlaying = false;
    Channel->isPlaying(&bPlaying);

    if (bPlaying)
        Channel->setPaused(true);
}

void CAudioSystem::ResumeSound(const FString& SoundName)
{
    // 채널에서 사운드 찾기
    auto Iter = Channels.find(SoundName);

    // 채널을 찾을 수 없는 경우
    if (Iter == Channels.end())
        return;

    // 해당 사운드의 채널 가져오기
    FMOD::Channel* Channel = Iter->second;

    // 채널이 정지 중이면 재개
    bool bPaused = false;
    Channel->getPaused(&bPaused);

    if (bPaused)
        Channel->setPaused(false);
}

void CAudioSystem::SetVolume(const FString& SoundName, float Volume)
{
    // 채널에서 사운드 찾기
    auto Iter = Channels.find(SoundName);

    // 채널을 찾을 수 없는 경우
    if (Iter == Channels.end())
        return;

    // 해당 사운드의 채널 가져오기
    FMOD::Channel* Channel = Iter->second;

    // 볼륨 설정 (0.0f ~ 1.0f 범위)
    Channel->setVolume(FMath::Clamp(Volume, 0.0f, 1.0f));
}

void CAudioSystem::SetPitch(const FString& SoundName, float Pitch)
{
    // 채널에서 사운드 찾기
    auto Iter = Channels.find(SoundName);

    // 채널을 찾을 수 없는 경우
    if (Iter == Channels.end())
        return;

    // 해당 사운드의 채널 가져오기
    FMOD::Channel* Channel = Iter->second;

    // 피치 설정 (0.5f: 반음, 2.0f: 두 배 높음)
    Channel->setPitch(FMath::Clamp(Pitch, 0.1f, 3.0f));
}

void CAudioSystem::SetPan(const FString& SoundName, float Pan)
{
    // 채널에서 사운드 찾기
    auto Iter = Channels.find(SoundName);

    // 채널을 찾을 수 없는 경우
    if (Iter == Channels.end())
        return;

    // 해당 사운드의 채널 가져오기
    FMOD::Channel* Channel = Iter->second;

    // 팬 설정 (-1.0f: 왼쪽, 0.0f: 중앙, 1.0f: 오른쪽)
    Channel->setPan(FMath::Clamp(Pan, -1.0f, 1.0f));
}

bool CAudioSystem::IsPlaying(const FString& SoundName)
{
    // 채널에서 사운드 찾기
    auto Iter = Channels.find(SoundName);

    // 채널을 찾을 수 없는 경우
    if (Iter == Channels.end())
        return false;

    // 해당 사운드의 채널 가져오기
    FMOD::Channel* Channel = Iter->second;

    // 채널이 재생 중인지 확인
    bool bPlaying = false;
    Channel->isPlaying(&bPlaying);

    // 재생 상태 반환
    return bPlaying;
}