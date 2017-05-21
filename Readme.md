# Statistical Protocol IDentification (SPID)

SPID is tool to identify network protocols based on the Kullback-Leibler divergence. It is a further development of a [https://www.iis.se/docs/The_SPID_Algorithm_-_Statistical_Protocol_IDentification.pdf](paper from Erik Hjelmvik). I re-implemented the algorithm in C++, added UDP support, and added additional measurements to improve the identification of media protocols.

## Installation

It should be enough to just type `make` to compile the program.

## Usage

With the `--help` option you will get the following list options:

```
$ ./spid --help
Usage: ./spid options
  -p, --promiscous              enables promiscous mode
  -r, --read-pcap <pcap_file>   reads an pcap file in
  -i, --interface <interface>   sets the interface to listen on

  -l, --learn <db_file>         write new statistics to the file
  -n, --name <name>             name of the protocol or category
  -f, --fingerprintdb <db_file> database to identifiy

  -m, --max <number>            maximal numbers of trained flows
  -d, --debug                   print additionl debug messages
  -h, --help                    print this help page
  -v, --version                 print version number
```

To identify protocols live you can use the following options:

```
$ ./spid -p -i <interface> -f fingerprint-db.txt
```
