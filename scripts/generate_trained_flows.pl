#!/usr/bin/env perl -w

use strict;
use warnings;

use feature ':5.10';

my @protos   = ('bittorre', 'ftp', 'irc', 'ogmstrea', 'rtmp', 'ssh', 'telnet',
                'flash', 'http', 'mms', 'pop3', 'rtp', 'smtp', 'ssl', 'tftp',
                'mpegts', 'wmvstre');
my $pwd      = '/home/cit/Dropbox/Bachelor/fhspid/';
my $captures = '/home/cit/Studium/7.Sem/Captures/';
my $db       = $pwd . 'test.db';
my $learn    = $pwd . 'scripts/learn_directory.pl';
my $stat     = $pwd . 'scripts/check_statistics.pl';
my $result   = $pwd . 'scripts/results.pl';

my $max = 15;

for (my $i = 1; $i <= $max; $i++) {
    unlink($db);
    system("perl $learn $captures $i");
    system("perl $stat $captures $i >tmp.txt");
    
    foreach my $proto (@protos) {
        system("perl $result $proto tmp.txt $i >> ../auswertungen/$proto.txt");
    }
    
    unlink($pwd.'tmp.txt');
}

