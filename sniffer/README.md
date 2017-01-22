#Sniffer Module
Enables the core ESP8266 SDK promiscuous mode functionality with a Python handler method.

##Python API:
>import sniff  #Imports the Sniffer module

###sniff.Sniffer( handler( *bytearray* ) )
Changes the WiFi mode to STATION, and listens for packets on the current WiFi channel.
All packets are sent to the *handler* method for interpretation.

>def process(packet):
>	print(packet) 
>sniff.Sniffer(process)
>...
>*#bytearray(b'\xa7\x10\...\xe4\x00')*

###sniff.channel( channel )
Set the current WiFi channel, even while sniffing.
Ranges from 1 to 14, though 12 - 14 are reserved in North America.

>sniff.channel(5) *#changes the channel to 5*

