#!/usr/bin/env perl -w
########################################################################
# learn_directory
# A simple script to learn a whole directory with it's subdirectorys.
# Every subdirectory is a new protocol or application and it contains
# the captured pcap files.
# Florian Adamsky, 2010 (florian\@iem.fh-friedberg.de)
########################################################################
use strict;
use warnings;
use feature ':5.10';

use File::Find;
use FindBin qw($Bin);


($#ARGV == 0 || $#ARGV == 1)
    or die "Usage: $0 [directory] [max]\n";

my $directory = $ARGV[0];  # directory of all pcap files
my $max       = $ARGV[1];  # maximal trained flows (only for research)

my $pwd      = $Bin . '/../';
my $database = $pwd . 'fingerprint.db';
my $spid     = $pwd . 'spid';
my $cnt      = 0;

########################################################################
find sub {
########################################################################
    return if -d;

    # take the directory as the protocol name
    my ($protocol) = $File::Find::dir =~ /\/(\w+)$/;
    $protocol      = substr $protocol, 0, 8;

    print "File: " . $_, "\n";

    my $max_cmd = '';
    if ($#ARGV == 1) {
        $max_cmd = '-m $max ';
    }

    if ($cnt == 0) {
        system($spid, $max_cmd, '-l', $database, '-n',
               $protocol, '-r', $_);
    }
    else {
        system($spid, $max_cmd, '-f', $database, '-l',
               $database, '-n', $protocol, '-r', $_);
    }
    $cnt++;
}, $directory;
