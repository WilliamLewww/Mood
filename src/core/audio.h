#pragma once
#include <algorithm>
#include <vector>
#include <bass.h>
#include <bass_fx.h>

class Audio {
private:
	std::vector<HSTREAM> streams;
public:
	void initialize(HWND hwnd);
	void quit();

	void playSoundFile(const char* file);

	int getStreamIsActive(HSTREAM stream);

	void playStream(HSTREAM stream);
	void stopStream(HSTREAM stream);
	void resetStream(HSTREAM stream);
	void removeStream(HSTREAM stream);
	HSTREAM* createStreamFromFile(const char* file);
	void changeStreamPitchSemitone(int index, float amount);
};

extern Audio audio;