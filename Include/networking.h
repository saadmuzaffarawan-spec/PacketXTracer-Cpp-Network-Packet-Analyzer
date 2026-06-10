#pragma once

#include "packetdetail.h"

#include "PcapLiveDevice.h"

#include <vector>

#include "analyzertool.h"

class PacketsParser : public AnalyzerTool{
    public:
    Packetdetail parsedpacket(pcpp::RawPacket* rawPacket);
};

extern std::vector<Packetdetail> capturedPackets;

void onPacketArrives(pcpp::RawPacket* rawPacket,
                     pcpp::PcapLiveDevice* device,
                     void* userdata);