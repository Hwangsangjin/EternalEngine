#include "Precompiled.h"
#include "ActorComponent.h"
#include "Actor/Actor.h"

CActorComponent::CActorComponent(CActor* InActor, const FString& InName)
    : Owner(InActor)
    , Name(InName)
{
}
