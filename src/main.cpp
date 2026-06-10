#include "Networking.h"
#include "ui.h"

#include "PcapLiveDeviceList.h"
#include "PcapLiveDevice.h"

#include <iostream>
#include <vector>

using namespace pcpp;

int main(){
    std::vector<PcapLiveDevice*> devices = PcapLiveDeviceList::getInstance().
    getPcapLiveDevicesList();

    std::cout <<"Available Adapters:\n\n";

    for (int i = 0; i< devices.size(); i++){
        std::cout << i << " : "
        << devices[i]->getDesc()
        << std::endl;
    }

    int choice;
    std::cout <<"Select Adapter Number: ";
    std::cin >> choice;

    try{
    if(choice < 0 || choice >= devices.size()){
        throw "Invalid adapter number!";
      }
    }

    catch(const char* error){

    std::cout << error << std::endl;
    return 1;

    }

    PcapLiveDevice* selectedDevice = devices[choice];

    if(!selectedDevice->open())
    {
        std::cout<< "Could not open device. Run CMD as Administrator.\n";
        return 1;
    }

    selectedDevice->startCapture(onPacketArrives, nullptr);

    std::cout<<"\nCapturing Packets...\n"
    <<"Press Enter To Stop.\n";

    // std::cin.ignore();//ignores the first enter key pressed
    // std::cin.get();// to recieve the second enter key pressed
    
    std::cout << "Before RunUI\n";

    RunUI();

    std::cout << "After RunUI\n";

    selectedDevice->stopCapture();
    
    selectedDevice->close();

    return 0;
}