#pragma once
#include <random>

namespace GameRandomGenerator {

	class RandomNumber {

	public:

		RandomNumber() {
			std::random_device rd;
			m_generator.seed(rd());
		}

		explicit RandomNumber(unsigned int seed) : m_generator(seed) {}

		float getFloat(float minNum = 0.f, float maxNum = 90000.f) {
			std::uniform_real_distribution<float> distrib(minNum, maxNum);
			return distrib(m_generator);
		}

		int getInt(int minNum = 0, int maxNum = 90000) {
			std::uniform_int_distribution<int> distrib(minNum, maxNum);
			return distrib(m_generator);
		}

	private:
		std::mt19937 m_generator;
	};

}

extern GameRandomGenerator::RandomNumber randomGenerator;

