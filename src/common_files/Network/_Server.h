﻿// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class VectorBufferRTS;


class Server : public Object
{
    URHO3D_OBJECT(Server, Object);

public:
    Server(Context *context = TheContext);
    virtual ~Server();
    bool Start(uint16 port);
    bool IsRunning();
    Vector<SharedPtr<Connection>> GetConnections();
    void SendToAll(int msgID, const VectorBufferRTS &msg);
    void Disconnect();
    void SetSimulatedLatency(int timeMS);
    void SetSimulatedPacketLoss(float probability);

private:
    Network *network = nullptr;

    DEFAULT_MEMBERS(Server);
};