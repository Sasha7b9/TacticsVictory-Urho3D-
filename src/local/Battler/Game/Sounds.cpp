// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "Sounds.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VariantMap Sounds::sounds;
PODVector<SoundSource3D*> sources;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sounds::Init()
{
    sounds[StringHash(Sound_Explosion)] = gCache->GetResource<Sound>("Sounds/ExplosionMissile.wav");
    Node *nodeSource = gScene->CreateChild("Sound");
    SoundSource3D* soundSource = nodeSource->CreateComponent<SoundSource3D>();
    soundSource->SetDistanceAttenuation(1.0f, 5.0f, 0.01f);
    soundSource->SetSoundType(SOUND_EFFECT);
    sources.Push(soundSource);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
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
    }

    source->GetNode()->SetPosition(position);
    source->Play((Sound*)sounds[StringHash((uint)type)].GetPtr());
}