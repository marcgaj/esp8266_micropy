#Sniffer Module
Enables the core ESP8266 SDK promiscuous mode functionality with a Python handler method.

##Python API:
>import sniff  #Imports the Sniffer module

###sniff.Sniffer( handler( *bytearray* ) )
Changes the WiFi mode to STATION, and listens for packets on the current WiFi channel.
All packets are sent to the *handler* method for interpretationas a _bytearray_.

>def process(packet):
>	print(packet) 
>sniff.Sniffer(process)
>
>*#bytearray(b'\xa7\x10\...\xe4\x00')*

###sniff.channel( channel )
Set the current WiFi channel, even while sniffing.
Ranges from 1 to 14, though 12 - 14 are reserved in North America.

>sniff.channel(5)     *#changes the channel to 5*

###ESP8266SDK Extensions
####sniff.prommode(0=disable,1=enable) => sdk_api::wifi_promiscuous_enable(int)
Extends the *wifi_promiscuous_enable()* function to a Python interface. Enables (1) or disables (0) the promiscuous mode functionality (and callback handler).

####sniff.opmode() => sdk_api::wifi_set_opmode_current(0=Station_Mode,1=SoftAP_Mode,2=Station+SoftAP_Mode)
A Python method to execute *wifi_set_opmode_current(_MODE_)*, which sets the currently operating WiFi mode.

####sniff.opmode_flash() => sdk_api::wifi_set_opmode(0=Station_Mode,1=SoftAP_Mode,2=Station+SoftAP_Mode)
A Python method to execute *wifi_set_opmode(_MODE_)*, which sets the currently operating WiFi mode, and saves the change into the flash memory.

####sniff.disc() => sdk_api::wifi_station_disconnect()
Extends the *wifi_station_disconnect()* function to a Python interface and disconnects the current WiFi connection(s).





//*********************************************************************************************
//Direct interfaces to several promiscuous mode or related methods from the ESP8266 NON-OS SDK.
// sniff.prommode(0=disable,1=enable): wifi_promiscuous_enable(int)
//
// sniff.station(): sets the wifi operation mode to station mode
//
// sniff.disc(): disconnects the wifi station (needs to be done before enabling the sniffer) 
//*********************************************************************************************
