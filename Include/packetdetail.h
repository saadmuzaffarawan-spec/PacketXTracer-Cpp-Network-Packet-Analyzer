#pragma once

#include <String>
#include <iostream>

class Packetdetail{
private:
    std::string SourceIp;
    std::string DestIp;
    std::string Protocol;
    int SrcPort;
    int DestPort;
    double size;

public:
    static int totalPackets;

    Packetdetail(){
        SourceIp = "NULL";
        DestIp = "NULL";
        Protocol = "UNKNOWN";
        SrcPort = 0;
        DestPort = 0;
        size = 0;
        totalPackets++;
    }

    Packetdetail(std::string src, std::string dst, std::string proto, int sp, int dp, double s){
        SourceIp = src;
        DestIp = dst;
        Protocol = proto;
        SrcPort = sp;
        DestPort = dp;
        size = s;
        totalPackets++;
    }

    std::string getSourceIp(){ return SourceIp; }
    std::string getDestIp(){ return DestIp; }
    std::string getProtocol(){ return Protocol; }
    int getSrcPort(){ return SrcPort; }
    int getDestPort(){ return DestPort; }
    double getSize(){ return size; }

    void setSourceIp(std::string v){ SourceIp = v; }
    void setDestIp(std::string v){ DestIp = v; }
    void setProtocol(std::string v){ Protocol = v; }
    void setSrcPort(int v){ SrcPort = v; }
    void setDestPort(int v){ DestPort = v; }
    void setSize(double v){ size = v; }

    friend std::ostream& operator<<(std::ostream& out, Packetdetail& p);
};