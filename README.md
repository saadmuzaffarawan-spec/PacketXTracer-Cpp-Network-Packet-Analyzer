# PacketXTracer — C++ Network Packet Analyzer

PacketXTracer is a C++ OOP-based network packet analyzer and packet sniffer built for live packet capture, protocol parsing, and cybersecurity traffic visualization.

The project uses Raylib for the graphical interface, PcapPlusPlus for packet parsing, Npcap for Windows packet capture, and libpcap/wpcap for low-level packet capture support.

It was developed as a second-semester C++ Object-Oriented Programming project, but the goal was to build something more practical than a normal console-based semester project. PacketXTracer connects C++ OOP concepts with real networking and cybersecurity fundamentals.

---

## Overview

PacketXTracer captures live network packets from a selected network adapter and displays useful packet information in a clean interface.

It helps beginners understand how packet analyzers work by showing important details such as:

* Source IP address
* Destination IP address
* Protocol type
* Source port
* Destination port
* Packet size
* Total captured packets
* Selected packet details

The project is useful for students learning C++, OOP, networking, packet analysis, cybersecurity basics, and traffic monitoring.

---

## Key Features

* Live packet capture from network adapters
* Network device selection through CLI
* TCP packet detection
* UDP packet detection
* ICMP packet detection
* ARP packet detection
* Unknown packet handling
* Source and destination IP extraction
* Source and destination port extraction
* Packet size display
* Packet counter
* Selected packet detail view
* File handling for saving captured packet logs
* Clean graphical interface using Raylib
* Modular C++ code structure
* Practical cybersecurity learning project

---

## Screenshots

### Main Menu

![PacketXTracer Main Menu](Screenshots/main-menu-dark.png)

### Live Packet Capture Dashboard

![PacketXTracer Live Capture Dashboard](Screenshots/live-capture-dashboard.png)

### CLI Device Selection

![PacketXTracer CLI Device Selection](Screenshots/cli-device-selection.png)

### Selected Network Adapter

![PacketXTracer Selected Adapter](Screenshots/selected-adapter.png)

### Packet Table View

![PacketXTracer Packet Table](Screenshots/packet-table.png)

### TCP Packet Detection

![PacketXTracer TCP Packet](Screenshots/tcp-packet.png)

### UDP Packet Detection

![PacketXTracer UDP Packet](Screenshots/udp-packet.png)

### Unknown Packet Handling

![PacketXTracer Unknown Packet](Screenshots/unknown-packet.png)

### Packet Log Saving

![PacketXTracer File Saving](Screenshots/file-saving.png)

---

## Demo

A demonstration video is available in the project release section.

The demo shows:

* Network adapter selection
* Live packet capture
* Packet table display
* Protocol detection
* Packet detail viewing
* Packet log saving

---

## Tech Stack

| Technology                  | Purpose                                    |
| --------------------------- | ------------------------------------------ |
| C++                         | Main programming language                  |
| Object-Oriented Programming | Project architecture and code organization |
| Raylib                      | Graphical user interface                   |
| PcapPlusPlus                | Packet parsing and protocol handling       |
| Npcap                       | Windows packet capture driver              |
| libpcap / wpcap             | Packet capture support                     |
| G++ / MinGW                 | Compilation and build process              |
| Windows                     | Main tested platform                       |

---

## How It Works

PacketXTracer follows this packet analysis flow:

```txt
Network Adapter
      ↓
Live Packet Capture
      ↓
Raw Packet
      ↓
Packet Parsing
      ↓
Protocol Detection
      ↓
Packet Detail Extraction
      ↓
GUI Display
      ↓
Packet Log Export
```

The program first lists available network adapters. After the user selects an adapter, PacketXTracer starts capturing live packets. Each raw packet is parsed, classified by protocol, and converted into readable information for display inside the graphical interface.

---

## OOP Concepts Used

This project applies multiple C++ Object-Oriented Programming concepts in a practical cybersecurity scenario.

### Classes and Objects

Packet information is stored and managed using classes instead of loose variables.

### Encapsulation

Packet details such as IP addresses, ports, protocol names, and packet size are handled through class methods.

### Abstraction

The low-level packet capture and parsing process is hidden behind simpler functions and classes.

### Static Members

A static packet counter is used to track the total number of captured packets.

### Operator Overloading

Packet details can be displayed in a cleaner and more readable format.

### Modular Programming

The project separates networking logic, packet details, UI handling, and main execution into different files.

---

## Project Structure

```txt
PacketXTracer-Cpp-Packet-Analyzer/
│
├── README.md
├── LICENSE
├── .gitignore
├── build.bat
├── compiling_command.txt
│
├── src/
│   ├── main.cpp
│   ├── Networking.cpp
│   └── ui.cpp
│
├── Include/
│   ├── analyzertool.h
│   ├── networking.h
│   ├── packetdetail.h
│   └── ui.h
│
├── Screenshots/
│   ├── main-menu-dark.png
│   ├── live-capture-dashboard.png
│   ├── cli-device-selection.png
│   ├── selected-adapter.png
│   ├── packet-table.png
│   ├── tcp-packet.png
│   ├── udp-packet.png
│   ├── unknown-packet.png
│   └── file-saving.png
│
├── Examples/
│   └── packetx_packets_log.txt
│
└── demo/
    └── README.md
```

---

## Requirements

Before building the project, install:

* Windows 10 or Windows 11
* G++ / MinGW
* Raylib
* PcapPlusPlus
* Npcap
* Npcap SDK
* libpcap / wpcap compatible libraries

Npcap should be installed properly because live packet capture depends on it.

---

## Build Instructions

Open Command Prompt and run:

```bat
cd /d C:\Packetanalyzer
build.bat
```

Or compile manually using:

```bat
cd /d C:\Packetanalyzer

C:\raylib\w64devkit\bin\g++.exe src\main.cpp src\Networking.cpp src\ui.cpp ^
-I"C:\Packetanalyzer\Include" ^
-I"C:\raylib\raylib\src" ^
-I"C:\PcapPlusPlus-25.05\Common++\header" ^
-I"C:\PcapPlusPlus-25.05\Packet++\header" ^
-I"C:\PcapPlusPlus-25.05\Pcap++\header" ^
-I"C:\Npcap-SDK\Include" ^
-L"C:\raylib\raylib\src" ^
-L"C:\PcapPlusPlus-25.05\build\Common++" ^
-L"C:\PcapPlusPlus-25.05\build\Packet++" ^
-L"C:\PcapPlusPlus-25.05\build\Pcap++" ^
-L"C:\Npcap-SDK\Lib\x64" ^
-lraylib ^
-lPcap++ -lPacket++ -lCommon++ ^
-lwpcap -lPacket ^
-lws2_32 -liphlpapi -lopengl32 -lgdi32 -lwinmm ^
-o PacketXTracer.exe
```

---

## How to Run

After building the project, run:

```bat
PacketXTracer.exe
```

For live packet capturing, run the program with administrator permission if required.

---

## Example Packet Log

PacketXTracer saves packet information in a readable format.

Example:

```txt
192.168.1.5 | 142.250.190.78 | TCP | 51522 --> 443 | 66 bytes
192.168.1.5 | 8.8.8.8 | UDP | 53021 --> 53 | 74 bytes
192.168.1.1 | 192.168.1.5 | ICMP | 0 --> 0 | 98 bytes
```

A sample packet log is available in:

```txt
Examples/packetx_packets_log.txt
```

---

## Why I Built This Project

I built PacketXTracer to connect classroom-level C++ OOP concepts with real cybersecurity and networking practice.

Many beginner C++ projects are based on simple console systems such as calculators, banking systems, or management systems. I wanted to build something more practical and closer to real cybersecurity tools.

Through this project, I learned how packet analyzers work, how live traffic is captured, how different protocols are detected, and how C++ classes can organize real network data.

---

## Educational Value

PacketXTracer is useful for:

* C++ students
* Cybersecurity beginners
* Networking students
* OOP learners
* Students building semester projects
* Beginners learning packet sniffing
* Learners exploring packet capture with Npcap and PcapPlusPlus

The project gives a practical introduction to packet analysis without making the interface too complex for beginners.

---

## Current Limitations

PacketXTracer is still a learning-focused project and has some limitations:

* Mainly tested on Windows
* Requires Npcap installation
* May require administrator privileges
* Does not yet include advanced filtering
* Does not yet support full deep packet inspection
* Does not yet support `.pcap` file import
* Export format is currently text-based
* UI can be improved further

---

## Future Improvements

Planned improvements include:

* Search packets by protocol
* Filter packets by IP address
* Filter packets by port number
* Export packet logs to CSV
* Add protocol-wise packet statistics
* Add traffic graphs
* Add `.pcap` file reading support
* Add better error handling
* Improve UI responsiveness
* Add installer or release package

---

## Disclaimer

This project is created for educational and ethical learning purposes only.

PacketXTracer should only be used on networks and devices where you have permission. It is intended to help understand networking, cybersecurity, and packet analysis concepts responsibly.

---

## Author

Saad Muzaffar Awan
BS Cyber Security Student
Pak-Austria Fachhochschule: Institute of Applied Sciences and Technology
Pakistan

---

## Keywords

C++ packet analyzer, C++ packet sniffer, network packet analyzer, packet sniffer project, cybersecurity C++ project, OOP cybersecurity project, Npcap packet capture, PcapPlusPlus packet analyzer, Raylib C++ GUI, libpcap Windows packet analyzer, TCP UDP ICMP packet parser, network traffic analysis tool.
