#pragma once
#include "../C03PacketPlayer.h"
class C04PacketPlayerPosition : public C03PacketPlayer
{
public:
	using C03PacketPlayer::C03PacketPlayer;
	static C04PacketPlayerPosition newObject(const Kisse::Maths::Vector3d& position, bool isOnGround, JNIEnv* env = Kisse::p_env);

	//on 1.7.10, packet is different, it contains a stance value, which is usually set to posY
	//and y is set to boundingBox.minY
	static C04PacketPlayerPosition newObject1_7_10(const Kisse::Maths::Vector3d& position, double stance, bool isOnGround, JNIEnv* env = Kisse::p_env);
protected:
	inline static Kisse::JavaClassV2 C04PacketPlayerPositionClass{ "net/minecraft/network/play/client/C03PacketPlayer$C04PacketPlayerPosition" };
};