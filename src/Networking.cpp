#include "IPv4Layer.h"
#include "TcpLayer.h"
#include "UdpLayer.h"
#include "IcmpLayer.h"
#include "ArpLayer.h"
#include "Packet.h"

#include "PcapLiveDeviceList.h"
#include "PcapLiveDevice.h"

#include <iostream>
#include <string>
#include <vector>

#include "networking.h"

using namespace pcpp;

int Packetdetail::totalPackets = 0;

std::ostream& operator<<(std::ostream& out, Packetdetail& p){
    out << p.getSourceIp() << " | "
        << p.getDestIp() << " | "
        << p.getProtocol() << " | "
        << p.getSrcPort() << " --> "
        << p.getDestPort() << " | "
        << p.getSize() << " bytes";
    return out;
}


Packetdetail PacketsParser::parsedpacket(RawPacket* rawPacket){
    Packet packet(rawPacket);

    Packetdetail info;
    info.setSourceIp("NULL");
    info.setDestIp("NULL");
    info.setProtocol("UNKNOWN");
    info.setSrcPort(0);
    info.setDestPort(0);
    info.setSize(0);

    TcpLayer* tcpLayer = packet.getLayerOfType<TcpLayer>();

    if(tcpLayer != nullptr){
        info.setSrcPort(tcpLayer->getSrcPort());
        info.setDestPort(tcpLayer->getDstPort());
        info.setSize(rawPacket->getRawDataLen());
        info.setProtocol("TCP");
    }
    
    UdpLayer* udpLayer = packet.getLayerOfType<UdpLayer>();

    if(udpLayer != nullptr){
        info.setSrcPort(udpLayer->getSrcPort());
        info.setDestPort(udpLayer->getDstPort());
        info.setSize(rawPacket->getRawDataLen());
        info.setProtocol("UDP");
    }

    IcmpLayer* icmpLayer = packet.getLayerOfType<IcmpLayer>();

    if(icmpLayer != nullptr){
        info.setSize(rawPacket->getRawDataLen());
        info.setProtocol ("ICMP");
    }
    
    ArpLayer* arpLayer = packet.getLayerOfType<ArpLayer>();

    if(arpLayer != nullptr){
        info.setSize(rawPacket->getRawDataLen());
        info.setProtocol ("ARP");
    }

    IPv4Layer* ipv4Layer = packet.getLayerOfType<IPv4Layer>();

    if(ipv4Layer != nullptr){
        info.setSourceIp(ipv4Layer->getSrcIPAddress().toString());
        info.setDestIp(ipv4Layer->getDstIPAddress().toString());
    }

    return info;
}

std::vector<Packetdetail> capturedPackets;
PacketsParser parser;

void onPacketArrives(RawPacket* rawPacket,
PcapLiveDevice* device,
void* userData){

    Packetdetail info = parser.parsedpacket(rawPacket);
    capturedPackets.push_back(info);

            std::cout << info << std::endl;
}