Remote UDP Network alarm  display for Inkpad 6 plus Eink display. 

send packets to display as UDP.  Begin with time in HH:MM format (24 hour) 
time only updates prefix with a "T" 
Phone call updates prefix with a "P" (displays in bottom box) 

GUI inkplate editor is at https://inkplate.io/home/gui-editor/ if modification is needed. 

Use the following bash script on a Unix host to update the clock every 5 min or so. Update IP to the IP of your inkplate. 


<pre> 
#!/bin/bash
# Update eink display
#
/bin/date +T%H:%M >/dev/udp/192.168.0.10/1234  

</pre>
To send an alarm or text line to the display from the following script and put what you want to send on the command line options. 

<pre>
#!/bin/bash
# Update eink display
#
/bin/date +%H:%M $* >/dev/udp/192.168.0.10/1234  
</pre>


use versions with a Prepended P to update the phone screen at the bottom from your pabx. 

# spectrum-eink2
