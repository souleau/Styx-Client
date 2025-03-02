#pragma once
#include "../../../Packet/Packet.h"
#include "../../../../../../Kisse/Maths/Maths.h"
class C03PacketPlayer : public Packet
{
public:
	using Packet::Packet;
	static C03PacketPlayer newObject(bool isOnGround, JNIEnv* env = Kisse::p_env); //not valid on 1.19.4

	Kisse::Maths::Vector3d getXYZ();
	void setXYZ(const Kisse::Maths::Vector3d& vector);

	Kisse::Maths::Vector2d getYawPitch();
	void setYawPitch(Kisse::Maths::Vector2d yawPitch);

	bool getOnGround();
	void setOnGround(bool state);

	bool getMoving();
	void setMoving(bool state);

	bool getRotating();
	void setRotating(bool state);
protected:
	inline static Kisse::JavaClassV2 C03PacketPlayerClass{ "net/minecraft/network/play/client/C03PacketPlayer" };
};