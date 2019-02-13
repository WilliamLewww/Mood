#include "timer.h"

Timer timer;

int Timer::getTime() {
	return elapsedTime;
}

float Timer::getTimeSeconds() {
	return (float)(elapsedTime) / 1000;
}

float Timer::getTotalTimeSeconds() {
	return totalTimeSeconds;
}

void Timer::setTime(int elapsedTime) {
	this->elapsedTime = elapsedTime;
	this->totalTimeSeconds += getTimeSeconds();
}