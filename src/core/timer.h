#pragma once

class Timer {
private:
	int elapsedTime;
	float totalTimeSeconds;
public:
	int getTime();
	float getTimeSeconds();
	float getTotalTimeSeconds();

	void setTime(int elapsedTime);
};

extern Timer timer;