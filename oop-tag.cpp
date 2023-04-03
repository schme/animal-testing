#include <chrono>
#include <random>

#define USE_FORI 0

struct ImportantAnimalStuff {
	bool needs_to_eat = true;
	int toys_for_christmas_deserved = 4;
	int more_space_taken_here[32] = {0};
};

class Animal {
public:
	Animal(int tag) : _tag(tag) {};
	virtual const char * greet() { return ""; }
	int tag() { return _tag; }
	void setTag(int tag) { _tag = tag; }
private:
	ImportantAnimalStuff stuff;
	int _tag;
};

class Cat : public Animal {
public:
	using Animal::Animal;
	const char * greet() override {
		return greeting;
	}
private:
	const char * greeting = "purr";
};

class Dog : public Animal {
public:
	using Animal::Animal;
	const char * greet() override {
		return greeting;
	}
private:
	const char *greeting = "woof";
};

class Donkey : public Animal {
public:
	using Animal::Animal;
	const char * greet() override {
		return greeting;
	}
private:
	const char *greeting = "heehaaw";
};

class Mammoth : public Animal {
public:
	using Animal::Animal;
	const char * greet() override {
		return greeting;
	}
private:
	const char *greeting = "toot";
};

class Snake : public Animal {
public:
	using Animal::Animal;
	const char * greet() override {
		return greeting;
	}
private:
	const char *greeting = "sssss";
};


Animal *create_random_animal(int id, int tag)
{
	switch (id) {
		case 0:
			return new Cat(tag);
		case 1:
			return new Dog(tag);
		case 2:
			return new Donkey(tag);
		case 3:
			return new Mammoth(tag);
		case 4:
			return new Snake(tag);
	}
	return nullptr;
}

int main(int argc, char *argv[])
{
	std::vector<Animal*> animals;

	// fill the data
	std::mt19937 engine(1234);
	std::uniform_int_distribution<int> distribution(0, 4);
	std::uniform_int_distribution<int> tags(0, std::numeric_limits<int>::max() - 1);

	static const int samples = 10000;
	static const int max_iterations = 10000;

	animals.reserve(samples * sizeof(Animal));

	for (int i=0; i < samples; ++i) {
		Animal *a = create_random_animal(distribution(engine), tags(engine));
		animals.emplace_back(a);
	}

	unsigned count_tags = 0;
	printf("Running with %d samples and %d iterations\n", samples, max_iterations);

	// run the test
	auto start_time = std::chrono::high_resolution_clock::now();
	for (int i=0; i < max_iterations; ++i) {
#if USE_FORI
		for (int i=0; i < animals.size(); ++i) {
			auto *animal= animals[i];
#else
		for (Animal *animal : animals) {
#endif
			auto answer = animal->greet();
			count_tags += animal->tag();
		}
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

	printf("%u\n", count_tags);
	printf("Time elapsed: ~%.2f seconds\n", elapsed_time / 1000.0 / 1000.0 );
	printf("Time per iteration: ~%ld microseconds\n", elapsed_time / max_iterations);
}
