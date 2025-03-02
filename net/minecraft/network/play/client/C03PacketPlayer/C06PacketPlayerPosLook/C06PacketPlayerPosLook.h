#pragma once
#include "../C03PacketPlayer.h"

class C06PacketPlayerPosLook : public C03PacketPlayer
{
public:
	using C03PacketPlayer::C03PacketPlayer;
	static C06PacketPlayerPosLook newObject(const Kisse::Maths::Vector3d& position, const Kisse::Maths::Vector2d& rotation, bool isOnGround, JNIEnv* env = Kisse::p_env);

	//on 1.7.10, packet is different, it contains a stance value, which is usually set to posY
	//and y is set to boundingBox.minY
	static C06PacketPlayerPosLook newObject1_7_10(const Kisse::Maths::Vector3d& position, double stance, const Kisse::Maths::Vector2d& rotation, bool isOnGround, JNIEnv* env = Kisse::p_env);
protected:
	inline static Kisse::JavaClassV2 C06PacketPlayerPosLookClass{ "net/minecraft/network/play/client/C03PacketPlayer$C06PacketPlayerPosLook" };
};