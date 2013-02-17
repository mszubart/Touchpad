#pragma once
/*
	getHostNameByAdapter puts host IP address into 'name' of max length 'namelen'.
	What does 'ByAdapterMagic' mean? I could waste my time on doing fancy combo box in 
	configuration window, letting you choose adapter by it's unicorntastic name, but
	I do not give a shit :) So this 'algorithm' does some magic.
	Preffered adapter types : Ehternet, WiFi, PPP. Adapter with least 'Index' and valid IP 'Context'
	will be chosen. And if you don't have such one then '127.0.0.1' 
	(which basically will listen on everything you have) will be used.
	
	Yes it is shitty solution but as I mentioned above, I will not waste my time
	on fucking with windows api.
*/
void getHostNameByMagic(char* name, int namelen);
