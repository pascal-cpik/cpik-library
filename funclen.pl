#!/usr/bin/perl


my $r = qx(cat sim.lst | grep -E '[0-9]{5} C18_');

my $addr=-1;
my $lastaddr=-1;
my $funcname='';
foreach my $line (split /^/, $r) {
  if($line =~ /^([0-9A-F]+) +\d+ ([^ \n\r]+)/) {
#     print("***",$addr,$lastaddr,$funcname,$1,$2);
    $addr = hex($1);
    if($lastaddr>0) {
      printf("%20s %3d bytes\n",$funcname,$addr-$lastaddr);
    }
    $funcname = $2;
    $lastaddr=$addr;
  } 
}

exit 0;
