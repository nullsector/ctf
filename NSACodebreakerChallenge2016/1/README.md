Task1- Information Gathering and Triage, Part1

A military organization captured a laptop of a known explosives expert within a terrorist organization.  Further analysis revealed that the laptop contained a debug version of the remote client interface that the individual used to communicate with the IEDs. To help detect other client programs in use, we are cataloging binary signatures and basic network signatures for every version of the IED software we find. To support these efforts, your task is to compute the SHA256 hash of the client binary and identify the source and destination TCP ports that it uses when connecting to an IED.


SHA256: 7c8cd1ca7d75175b768cd16dc40359acf7eb2b5d58a28ce146660ef4ad5f4ec7

client.exe sends a TCP syn packet to remote port 8080 via local port 17920
