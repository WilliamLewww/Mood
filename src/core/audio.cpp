#include "audio.h"

Audio audio;

void Audio::initialize(HWND hwnd) {
	BASS_FX_GetVersion();
	BASS_Init(-1, 44100, 0, hwnd, NULL);
}

void Audio::playSoundFile(const char* file) {
	HSTREAM stream = BASS_StreamCreateFile(FALSE, file, 0, 0, 0);
	BASS_ChannelPlay(stream, false);
}

int Audio::getStreamIsActive(HSTREAM stream) {
	return BASS_ChannelIsActive(stream);
}

void Audio::playStream(HSTREAM stream) {
	BASS_ChannelPlay(stream, false);
}

void Audio::stopStream(HSTREAM stream) {
	BASS_ChannelStop(stream);
}

void Audio::resetStream(HSTREAM stream) {
	BASS_ChannelSetPosition(stream, 0, BASS_POS_RESET);
}

void Audio::removeStream(HSTREAM stream) {
	streams.erase(std::remove(streams.begin(), streams.end(), stream), streams.end());
}

HSTREAM* Audio::createStreamFromFile(const char* file) {
	streams.push_back(BASS_StreamCreateFile(FALSE, file, 0, 0, 0));
	return &streams[streams.size() - 1];
}

void Audio::changeStreamPitchSemitone(int index, float amount) {
	BASS_BFX_PITCHSHIFT param = { 0, amount, 2048, 8,  BASS_BFX_CHANALL };
	HFX handle = BASS_ChannelSetFX(streams[index], BASS_FX_BFX_PITCHSHIFT, 1);
	BASS_FXSetParameters(handle, &param);
}

void Audio::quit() {
	BASS_Free();
}