#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

class btRigidBody;
class Module;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	PhysBody3D();
	~PhysBody3D();

	btRigidBody* GetBody();
	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetAsSensor(bool isSensor);

	bool isChecked;
	bool isDeath;
private:
	btRigidBody* body = nullptr;
	bool isSensor;
public:
	p2List<Module*> collision_listeners;
};

#endif // __PhysBody3D_H__