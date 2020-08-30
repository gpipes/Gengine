#pragma once
#include "guy.hpp"
#include "utility.hpp"

Guy::Guy() 
	: GameObjectBase("char.bmp", 30, 40, 2)
{
	std::vector<AnimationInfo> walkingRightFrames = {
		{{0, 2}, 10},
		{{1, 2}, 10},
		{{2, 2}, 10},
		{{3, 2}, 10}
	};
	AnimationVector walkingRightInfo(walkingRightFrames, true, true);

	std::vector<AnimationInfo> walkingDownFrames{
		{{0,0}, 10},
		{{1,0}, 10},
		{{2,0}, 10},
		{{3,0}, 10}
	};
	AnimationVector walkingDownInfo(walkingDownFrames, true, true);
	addAnimationState(WALKING_RIGHT, walkingRightInfo);
	addAnimationState(WALKING_DOWN, walkingDownInfo);
	setCurrentAnimationState(WALKING_RIGHT);
} 