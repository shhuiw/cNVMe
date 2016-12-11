/*
This file is part of cNVMe and is released under the MIT License
(C) - Charles Machalow - 2016
Main.cpp - An implementation file for the Main entry
*/

#include "Strings.h"
#include "PCIe.h"

#include <iostream>

using namespace cnvme;


int main()
{
	// This is testing code.
	
	pci::PCIExpressRegisters p;

	LOG_SET_LEVEL(5);

	p.getPciExpressRegisters().PciHeader->ID.VID = 0xBB;
	p.getPciExpressRegisters().PciHeader->ID.DID = 0xFF;

	Payload other(99999);
	memset(other.getBuffer(), 0xff, 99999);
	p.writeHeaderAndCapabilities(other); // should do FLR

	std::this_thread::sleep_for(std::chrono::seconds(2));

	p.getPciExpressRegisters().PXCAP->PXDC.IFLR = 1;  // Does another FLR

	std::this_thread::sleep_for(std::chrono::seconds(2));

	char c = '1';
	std::cin >> c;

	// End testing code.
}