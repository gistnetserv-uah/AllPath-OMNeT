//
// Copyright (C) 05/2013 Elisa Rojas
//      Implements the base class for UDPFlowGenerator and TCPFlowGenerator, which share functionality
/*
 * Copyright (C) 2018 Elisa Rojas(1), Hedayat Hosseini(2);
 *                    (1) GIST, University of Alcala, Spain.
 *                    (2) CEIT, Amirkabir University of Technology (Tehran Polytechnic), Iran.
 *                    INET 3.6.3 adaptation
*/
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef WAPB_SRC_SIMULATIONMODELS_FLOWMODELS_FLOWGENERATORBASE_H_
#define WAPB_SRC_SIMULATIONMODELS_FLOWMODELS_FLOWGENERATORBASE_H_

#include <omnetpp.h>
#include "inet/networklayer/contract/ipv4/IPv4Address.h"
#include "inet/linklayer/common/MACAddress.h"
#include <string>

#include "src/simulationmodels/flowmodels/UDPFlowHost.h"

namespace wapb {
using namespace inet;

class FlowGeneratorBase : public cSimpleModule
{
    //friend class UDPFlowHost;
    friend class StatisticCollector;

   protected:

      //To save info about all the nodes in the network
      struct NodeInfo {
          NodeInfo() {isAdhoc=false;}
          std::string fullName;
          std::string nedTypeName;
          bool isAdhoc;
      };
      typedef std::vector<NodeInfo> NodeInfoVector;

      //To save info only about the Adhoc nodes in the network
      struct AdhocInfo {
          std::string fullName;
          IPv4Address ipAddress;
          MACAddress macAddress;
          UDPFlowHost * pUdpFlowHost; //Module in the host that generates the traffic
          unsigned int weight;
          unsigned int nFlowSource; //# of flows whose source was this host
          unsigned int nFlowDestination; //# of flows whose destination was this host
          unsigned int averageSizeSource; //Average flow size as source
          unsigned int averageSizeDestination; //Average flow size as destination
      };
      typedef std::vector<AdhocInfo> AdhocInfoVector;

      //To save info only about the host with weight != 1 in the network
      struct HostWeight {
          IPv4Address ipAddress;
          unsigned int weight;
      };
      typedef std::vector<HostWeight> HostWeightVector;

      //To save info about src and dst for route statistics
      struct DstSrcs {
          std::string dst;
          std::vector<std::string> srcs;
      };
      typedef std::vector<DstSrcs> DstSrcsVector;

      std::vector<L3Address> excludedAddresses;
      HostWeightVector hostsWeights;
      simtime_t stopTime;

      simtime_t maxInterval;
      simtime_t intvlStartTime;
      simtime_t intvlLastPkTime;
      double intvlSumDelay; // sum of the delay in each interval
      double intvlAverageDelay; // average of the delay in each interval
      unsigned long long intvlNumPackets;


      int numSent;
      int numReceived;

      int numSessions;

      unsigned long long numSentInbyte;
      unsigned long long numSentInPacket;
      unsigned long long numReceivedInbyte;
      unsigned long long numReceivedInPacket;

      double goodputRatio;
      double averageendToEndDelay;


      NodeInfoVector nodeInfo; //Vector that contains the topology, it will be of size topo.nodes[]
      AdhocInfoVector adhocInfo; //Vector that contains only the adhoc hosts in the topology and their IP and MAC addresses

      std::vector<std::string> generatedFlows; //Vector that contains the strings of the generated flows

      // statistic vectors
      cOutVector averageEndToEndDelayVector;
      cOutVector averageEndToEndDelayIntervalVector;
      cOutVector goodputRatioVector;


   protected:
     // virtual int numInitStages() const  {return 4;} //At least 3 (=4-1) because we need FlatNetworkConfigurator to be initialized (and it does at stage 2)
      virtual int numInitStages() const  {return NUM_INIT_STAGES;} //All stages can be used for initialize(int stage)
      virtual void initialize(int stage);
      virtual void extractTopology();
      virtual unsigned int getHostWeight(IPv4Address host);
      virtual void getRandomSrcDstIndex(int& iSource, int& iDestination);
      virtual void startRandomFlow();
      virtual void handleMessage(cMessage *msg);
      virtual void processPacket(cPacket *msg);

      virtual void accumulateReceivedData(simtime_t now, simtime_t endToEndDelay, unsigned long long numReceivedInPacket, unsigned long long numReceivedInbyte);
      virtual void beginNewInterval(simtime_t now); //, simtime_t endToEndDelay, unsigned long long numReceivedPacket);
      virtual void accumulateSentData(unsigned long long numSentInPacket, unsigned long long numSentInbyte);

      virtual void finish();
};

#endif /* WAPB_SRC_SIMULATIONMODELS_FLOWMODELS_FLOWGENERATORBASE_H_ */
} //namespace wapb
