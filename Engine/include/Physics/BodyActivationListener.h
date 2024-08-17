﻿#pragma once
#include "Debug.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
namespace Imp::Phys {
	class BodyActivationListener final : public JPH::BodyActivationListener
	{
	public:
		virtual void		OnBodyActivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override;

		virtual void		OnBodyDeactivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override;
	};

}
