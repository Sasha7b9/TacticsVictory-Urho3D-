#include <stdafx.h>


#include "Sounds.h"


VariantMap Sounds::sounds;


PODVector<SoundSource3D*> sources;


void Sounds::Init()
{
    sounds[StringHash(Sound_Explosion)] = gCache->GetResource<Sound>("Sounds/ExplosionMissile.wav");
    Node *nodeSource = gScene->CreateChild("Sound");
    SoundSource3D* soundSource = nodeSource->CreateComponent<SoundSource3D>();
    soundSource->SetDistanceAttenuation(1.0f, 50.0f, 1.0f);
    soundSource->SetSoundType(Urho3D::SOUND_EFFECT);
    sources.Push(soundSource);
}


void Sounds::Play(SoundType type, const Vector3 &position)
{
    SoundSource3D *source = nullptr;
    for (auto src : sources)
    {
        if (!src->IsPlaying())
        {
            source = src;
            break;
        }
    }
    
    if (!source)
    {
        Node *nodeSource = gScene->CreateChild("Sound");
        source = (SoundSource3D*)nodeSource->CloneComponent(sources[0]);
        sources.Push(source);
        URHO3D_LOGINFOF("%d sounds", sources.Size());
    }

    source->GetNode()->SetPosition(position);
    source->Play((Sound*)sounds[StringHash(type)].GetPtr());
}