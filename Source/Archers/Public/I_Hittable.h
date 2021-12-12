#pragma once

#include "I_Hittable.generated.h"

UINTERFACE(MinimalAPI)
class UHittableInterface : public UInterface
{
	GENERATED_BODY()
	
};

class IHittableInterface
{
 GENERATED_BODY()
public:
	virtual void TryToHit() = 0;
	
};
