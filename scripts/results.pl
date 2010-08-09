#!/usr/bin/env perl -w

use strict;
use warnings;

($#ARGV == 2)
    or die "Usage: $0 [protocol]\n";

my $proto  = $ARGV[0];
my $file   = $ARGV[1];
my $cnt    = $ARGV[2];
my $dir = '/home/cit/Dropbox/Bachelor/fhspid/';

my $tp = 0;
my $fp = 0;
my $recall;

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
            #print "Recall $recall\n";
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
#   print "Precision: $precision\n";
my $fmeasure = sprintf("%.2f", (2*$precision*$recall)/($recall+$precision));
#print "F-Measure: $fmeasure\n";
print "$cnt $fmeasure\n";
close($fh);
#}

