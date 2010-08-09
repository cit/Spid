#!/usr/bin/env perl -w
########################################################################
# check_statistics
# A simple script that checks how good the identifcation works on a
# whole directory and prints the result a nice and shiny table.
# Florian Adamsky, 2010 (florian@adamsky.it)
########################################################################
use strict;
use warnings;
use feature ':5.10';

use FindBin qw($Bin);
use File::Find;
use Text::ASCIITable;

($#ARGV == 0 or $#ARGV == 1)
    or die "Usage: $0 [directory] [max]\n";

my $max = $ARGV[1];

my $pwd      = $Bin . '/../';
my $database = $pwd . 'fingerprint.db';
my $spid     = $pwd . 'spid';
my $table    = Text::ASCIITable->new({ headingText => 'Auswertungen'});

$table->setCols('Protokoll', 'Erkannt', 'Anzahl', 'Prozentual');
my %statistics  = ();
my %statistics2 = ();

my $tmp = '';
my $cnt = 0;

find(\&count, @ARGV );

count();

print $table;

########################################################################
sub count {
########################################################################
    return if -d;
    my ($dir) = $File::Find::dir =~ /\/(\w+)$/;

    $tmp = $dir
        if $cnt == 0;

    if ($dir ne $tmp) {
        $table->addRow($tmp, '', '', '');

        foreach my $key (sort hashValueDescendingNum(keys %statistics)) {
            if ($tmp eq $key) {
                $table->addRow('*', $key, $statistics{$key},
                               sprintf("%.2f",($statistics{$key}/$cnt)*100).'%');   
            }
            else {
                $table->addRow('', $key, $statistics{$key},
                               sprintf("%.2f",($statistics{$key}/$cnt)*100).'%');
            }
        }
        $table->addRowLine();
 
        %statistics = ();
        $tmp = $dir;
        $cnt = 0;
    }

    my $cmd;
    if ($#ARGV == 0) {
        open($cmd, "$spid -f $database -r $_ 2> /dev/null|")
            or die "Failed: $!\n";        
    }
    elsif ($#ARGV == 1) {
        open($cmd, "$spid -m $max -f $database -r $_ 2> /dev/null|")
            or die "Failed: $!\n";
    }
    
    while ( <$cmd> ) {
        if (/guess/) {
            my ($proto) = $_ =~ /it\sis\s(\w+)$/;
            $statistics{$proto}++;
            $cnt++;
        }
    }
    close($cmd);
}

########################################################################
sub hashValueDescendingNum {
########################################################################
   $statistics{$b} <=> $statistics{$a};
}

