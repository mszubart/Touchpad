#include "NetIfaceHelpers.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#define LO_ADDR "127.0.0.1"

#include "Socket.h"

void getHostNameByMagic(char* name, int namelen)
{
	if(namelen < 16){
		throw ts::socket_exception("gethostnamebymagic: namelen is too small (<16)");
	}

	IP_ADAPTER_INFO  *pAdapterInfo, *iface=NULL;
	ULONG            ulOutBufLen;
	DWORD            dwRetVal;

	pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC( sizeof(IP_ADAPTER_INFO) );
	ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS) {
		FREE (pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC ( ulOutBufLen );
	}

	if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) != ERROR_SUCCESS) {
		goto ending;
	}

	PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
	int minIdx = 0xFFFFFFFF;
	while (pAdapter) {

		if(pAdapter->IpAddressList.Context !=0)
		{
			if(pAdapter->Type == MIB_IF_TYPE_ETHERNET || 
				pAdapter->Type == IF_TYPE_IEEE80211 ||
				pAdapter->Type == MIB_IF_TYPE_PPP){

					if(pAdapter->Index < minIdx){
						iface = pAdapter;
						minIdx = iface->Index;
					}
			}
		}
		
		pAdapter = pAdapter->Next;
	}

ending:
	if(iface == NULL){
		if(strlen(LO_ADDR)+1 <= namelen)
			memcpy(name, LO_ADDR, strlen(LO_ADDR)+1);
	}
	else{
		if(strlen(iface->IpAddressList.IpAddress.String)+1 <= namelen){
			memcpy(name, iface->IpAddressList.IpAddress.String, strlen(iface->IpAddressList.IpAddress.String)+1);
		}
	}

	if (pAdapterInfo)
		FREE(pAdapterInfo);

}
