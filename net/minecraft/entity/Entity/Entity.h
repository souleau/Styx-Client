#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../util/AxisAlignedBB/AxisAlignedBB.h"
#include "../../../../Kisse/Maths/Maths.h"

class Entity : public Object
{
public:
	using Object::Object;

	Kisse::Maths::Vector3d getPosition() const;
	Kisse::Maths::Vector3d getLastTickPosition() const;
	Kisse::Maths::Vector3d getMovementVector(float partialTicks) const; //(currpos - lastpos) * partial ticks
	Kisse::Maths::Vector3d getRenderPos(float partialTicks) const;
	Kisse::Maths::Vector2d getRotation() const;
	Kisse::Maths::Vector2d getPrevRotation() const;
	Kisse::Maths::Vector2d getRenderRotation(float partialTicks) const;
	Kisse::Maths::Vector3d getMotion() const;
	bool isOnGround() const;
	bool isSprinting() const;
	int getHurtResistantTime() const;
	int getTicksExisted() const;
	AxisAlignedBB getBoundingBox() const;
	float getEyeHeight() const;
	Entity getRidingEntity() const;
	int getEntityId() const;

	void setPosition(const Kisse::Maths::Vector3d& position);
	void setRidingEntity(Entity& entity);
	void setBoundingBox(const AxisAlignedBB& bb);
	void setSprinting(bool state);
	void setMotion(const Kisse::Maths::Vector3d& motion);
	void setRotation(const Kisse::Maths::Vector2d& yawPitch);
	virtual void setPositionAndUpdate(const Kisse::Maths::Vector3d& position);
protected:
	inline static Kisse::JavaClassV2 EntityClass{ "net/minecraft/entity/Entity" };
};