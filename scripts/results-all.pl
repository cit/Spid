#!/usr/bin/env perl -w

use strict;
use warnings;

($#ARGV == 0)
    or die "Usage: $0 [file]\n";

my $file   = $ARGV[0];

my @protos   = ('bittorre', 'ftp', 'irc', 'ogmstrea', 'rtmp', 'ssh', 'tftp',
                'telnet', 'flash', 'http', 'mms', 'pop3', 'rtp', 'smtp', 'ssl',
                'wmvstre', 'mpegts');

my $dir = '/home/cit/Dropbox/Bachelor/fhspid/';


foreach my $proto (@protos) {
    my $tp = 0;
    my $fp = 0;
    my $recall;

    print $proto;
    open(my $fh, "<", $file)
        or die "Could not $file open for reading: $!\n";
    while (<$fh>) {
        if (/$proto/) {
            if (/\*/) {
                $_ =~ /\s+(\d+)\s/;
                $tp = $1;
                $_ =~ /\s+(\d+)\.(\d+)\%/;
                $recall = $1 + ($2/100);
                #print "True Positive: $tp\n";
                #print " $tp\n";
                print " $recall";
            }
            else {
                if (/\s+(\d+)\s/) {
                    $fp += $1;
                }
            }
        }
    }
    #print "False Positive: $fp\n";
    my $precision = sprintf("%.2f", ($tp/($tp + $fp))*100);
    print " $precision";
    my $fmeasure = sprintf("%.2f", (2*$precision*$recall)/($recall+$precision));
    #print "F-Measure: $fmeasure\n";
    print " $fmeasure\n";
    close($fh);
}

