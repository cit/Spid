#!/usr/bin/env perl -w

use strict;
use warnings;

use feature ':5.10';

use Net::RawIP;
use IO::Socket::INET;

my $dest_ip = '127.0.0.1';
my $source_ip = '127.0.0.1';

die "You're not root"
  if ($> != 0);


for (my $count = 848; $count < 925; $count++) {
#my $count = 1460;

  say $count;
  my $a = new Net::RawIP;
  my $sock = IO::Socket::INET->new(PeerAddr => $dest_ip,
                                   PeerPort => '7070',
                                   Proto    => 'tcp')
    or die "Can't connect: $!\n";
  my $port = $sock->sockport();
  
  for (1...25) {
    $a->set({ ip => {saddr => $source_ip,
                     daddr => $dest_ip,
                    },
              tcp=> {dest => 7070,
                     source => $port,
                     syn => 1,
                     data => gen_str($count),
                    }
            });
    $a->send;
  }
  close $sock;
  sleep 1;
}



sub gen_str {
  my $length = shift;
  my $password;
  my $_rand;
  
  my @chars = split(" ",
                    "a b c d e f g h i j k l m n o
    p q r s t u v w x y z - _ % # |
    0 1 2 3 4 5 6 7 8 9");
  
  srand;
  
  for (my $i=0; $i < $length ;$i++) {
    $_rand = int(rand 41);
    $password .= $chars[$_rand];
  }
  return $password;
}
