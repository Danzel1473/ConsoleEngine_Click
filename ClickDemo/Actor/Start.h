#pragma once

#include "Actor/DrawableActor.h"

class Start : public DrawableActor
{
public:
	Start();

	virtual void Update(float deltaTime) override;
};