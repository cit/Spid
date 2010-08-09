#!/usr/bin/env perl -w

use strict;
use warnings;

use feature ':5.10';

use Net::RawIP;
use IO::Socket::INET;

die "You're not root"
  if ($> != 0);

for (my $count = 3; $count < 1480; $count++) {
  say $count;
  my $a = new Net::RawIP;
  my $sock = IO::Socket::INET->new(PeerAddr => '127.0.0.1',
                                   PeerPort => '7070',
                                   Proto    => 'udp')
    or die "Can't connect: $!\n";
  my $port = $sock->sockport();
  
  for (1...20) {
    $sock->send(gen_str($count));
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
