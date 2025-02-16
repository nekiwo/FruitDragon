/**
 * @file AudioStreamServer.hpp
 * @author nekiwo
 * @brief TCP/IP socket streamer that sends the audio stream and its metadata
 * @version 0.1
 * @date 2024-07-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef AUDIO_STREAM_SERVER
#define AUDIO_STREAM_SERVER

#include "audio/FileTree.hpp"
#include "audio/RawAudio.hpp"
#include "utils/Config.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;


class AudioStreamServer {
    public:
        AudioStreamServer();
        void startServer(FileTree &tree, Config &config);

        // HTTP requests
        void getLibrary();
        void getTrackFile();

        // WebSocket requests
        void getNextChunk();
        void getChunkAtSeconds();
        void getPlaybackData();
        void postPauseRequest();
        void postTimelineRequest();
        void postTrackRequest();
    private:
        RawAudio* currentTrack;
        bool playState = false;
        float trackSeconds = 0;
        uint32_t chunkIndex = 0;

        void startHTTPServer();
        void startWSServer();
};

#endif