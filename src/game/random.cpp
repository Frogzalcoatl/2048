#include "2048/game/random.hpp"
using namespace std;
static thread_local minstd_rand generator(random_device{}());
int getRandomInt(int min, int max) {
	static thread_local uniform_int_distribution<int> dist;
	return dist(generator, decltype(dist)::param_type{min, max});
}