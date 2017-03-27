//
// Created by Jury Verrigni on 3/27/17.
//

#include <Math/Math.h>
#include "Actor.h"

Actor::Actor()
{
    TranslationMatrix = Math::Translate(Matrix4::IdentityMatrix(), Vector3(-ActorLocation.X, -ActorLocation.Y, -ActorLocation.Z));
    RotationMatrix = 
}

void Actor::SetActorLocation(Vector3 NewLocation)
{
    ActorLocation = NewLocation;
}

Vector3 Actor::GetActorLocation()
{
    return ActorLocation;
}

