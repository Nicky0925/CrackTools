package main

import (
	"fmt"
	"log"

	"github.com/google/gopacket"
	"github.com/google/gopacket/layers"
	"github.com/google/gopacket/pcap"
)

func main() {
	device := "wlp3s0"
	filter := "tcp and port 80"

	handle, err := pcap.OpenLive(
		device, int32(0xFFFF), true, pcap.BlockForever,
	)
	if err != nil {
		log.Fatal(err)
	}
	defer handle.Close()
	if err := handle.SetBPFFilter(filter); err != nil {
		log.Fatal(err)
	}

	packetSource := gopacket.NewPacketSource(handle, handle.LinkType())
	for packet := range packetSource.Packets() {
		printPacketInfo(packet)
		jsonPacketInfo(packet)
	}
}

func printPacketInfo(packet gopacket.Packet) {
	ethernetLayer := packet.Layer(layers.LayerTypeEthernet)
	if ethernetLayer != nil {
		ethernetPacket, _ := ethernetLayer.(*layers.Ethernet)
		fmt.Println("Src MAC: ", ethernetPacket.SrcMAC)
		fmt.Println("Dst MAC: ", ethernetPacket.DstMAC)
	}

	ipLayer := packet.Layer(layers.LayerTypeIPv4)
	if ipLayer != nil {
		ip, _ := ipLayer.(*layers.IPv4)
		fmt.Println("Src IP Address: ", ip.SrcIP)
		fmt.Println("Dst IP Address: ", ip.DstIP)
	}

	tcpLayer := packet.Layer(layers.LayerTypeTCP)
	if tcpLayer != nil {
		tcp, _ := tcpLayer.(*layers.TCP)
		fmt.Println("Src Port: ", tcp.SrcPort)
		fmt.Println("Dst Port: ", tcp.DstPort)
	}
	fmt.Println()
}

func jsonPacketInfo(packet gopacket.Packet) {}
