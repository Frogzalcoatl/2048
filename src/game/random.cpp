#include "2048/game/random.hpp"
#include <random>

static thread_local std::minstd_rand generator(std::random_device{}());
int getRandomInt(int min, int max) {
	static thread_local std::uniform_int_distribution<int> dist;
	return dist(generator, decltype(dist)::param_type{min, max});
}