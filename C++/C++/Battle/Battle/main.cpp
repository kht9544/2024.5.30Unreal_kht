
#include "pch.h"

int main()
{
	srand(time(nullptr));

	World* world = new World();

	world->Battle2();

	delete world;

	return 0;
}