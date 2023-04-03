#include <chrono>
#include <random>
#include <array>

#define USE_FORI 1

struct ImportantAnimalStuff {
	bool needs_to_eat = true;
	int toys_for_christmas_deserved = 4;
	int more_space_taken_here[32] = {0};
};

struct Cat {
	ImportantAnimalStuff stuff;
	const char *greeting = "purr";
	int tag = -1;
};
struct Dog {
	ImportantAnimalStuff stuff;
	const char *greeting = "woof";
	int tag = -1;
};
struct Donkey {
	ImportantAnimalStuff stuff;
	const char *greeting = "heehaaw";
	int tag = -1;
};
struct Mammoth {
	ImportantAnimalStuff stuff;
	const char *greeting = "toot";
	int tag = -1;
};
struct Snake {
	ImportantAnimalStuff stuff;
	const char *greeting = "sssss";
	int tag = -1;
};

int main(int argc, char *argv[])
{

	// fill the data
	std::mt19937 engine(1234);
	std::uniform_int_distribution<int> distribution(0, 4);
	std::uniform_int_distribution<int> tags(0, std::numeric_limits<int>::max() - 1);

	static const int samples = 10000;
	static const int max_iterations = 10000;

	std::vector<Cat> cats;
	std::vector<Dog> dogs;
	std::vector<Donkey> donkeys;
	std::vector<Mammoth> mammoths;
	std::vector<Snake> snakes;

	cats.reserve(samples);
	dogs.reserve(samples);
	donkeys.reserve(samples);
	mammoths.reserve(samples);
	snakes.reserve(samples);


#define ADD_ANIMAL(arr, v) ((arr).emplace_back((v)))

	for (int i=0; i < samples; ++i) {
		int choice = distribution(engine);
		int tag = tags(engine);
		switch (choice) {
			case 0: {
				Cat animal;
				animal.tag = tag;
				ADD_ANIMAL(cats, animal);
			} break;
			case 1: {
				Dog animal;
				animal.tag = tag;
				ADD_ANIMAL(dogs, animal);
			} break;
			case 2: {
				Donkey animal;
				animal.tag = tag;
				ADD_ANIMAL(donkeys, animal);
			} break;
			case 3: {
				Mammoth animal;
				animal.tag = tag;
				ADD_ANIMAL(mammoths, animal);
			} break;
			case 4: {
				Snake animal;
				animal.tag = tag;
				ADD_ANIMAL(snakes, animal);
			} break;
		}
	}

	unsigned count_tags = 0;
	printf("Running with %d samples and %d iterations\n", samples, max_iterations);

	// run the test
	auto start_time = std::chrono::high_resolution_clock::now();
	for (int i=0; i < max_iterations; ++i) {
#if USE_FORI
		for (int i=0; i < cats.size(); ++i) {
			auto &animal = cats[i];
#else
		for (const auto &animal : cats) {
#endif
			auto answer = animal.greeting;
			count_tags += animal.tag;
		}
#if USE_FORI
		for (int i=0; i < dogs.size(); ++i) {
			auto &animal = dogs[i];
#else
		for (const auto &animal : dogs) {
#endif
			auto answer = animal.greeting;
			count_tags += animal.tag;
		}
#if USE_FORI
		for (int i=0; i < donkeys.size(); ++i) {
			auto &animal = donkeys[i];
#else
		for (const auto &animal : donkeys) {
#endif
			auto answer = animal.greeting;
			count_tags += animal.tag;
		}
#if USE_FORI
		for (int i=0; i < mammoths.size(); ++i) {
			auto &animal = mammoths[i];
#else
		for (const auto &animal : mammoths) {
#endif
			auto answer = animal.greeting;
			count_tags += animal.tag;
		}
#if USE_FORI
		for (int i=0; i < snakes.size(); ++i) {
			auto &animal = snakes[i];
#else
		for (const auto &animal : snakes) {
#endif
			auto answer = animal.greeting;
			count_tags += animal.tag;
		}
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

	printf("%u\n", count_tags);
	printf("Time elapsed: ~%.2f seconds\n", elapsed_time / 1000.0 / 1000.0 );
	printf("Time per iteration: ~%ld microseconds\n", elapsed_time / max_iterations);
}
