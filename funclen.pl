#!/usr/bin/perl

my $lst = @ARGV[0];

my $r = qx(cat $lst | grep -E '[0-9]{5} [CLX]18_');

my %addr=();

foreach my $line (split /^/, $r) {
  if($line =~ /^([0-9A-F]+) +\d+ ([^ \n\r]+)/) {
#      print("*** ",$addr," ",$lastaddr," ",$funcname,$1,$2,"\n");
    my $loc = hex($1);
    $funcname = $2;
    $addr{$funcname}=$loc;
  } 
}

# find "end marks"
my @funcs = grep /^X18_/, keys %addr;

foreach my $endf (sort @funcs) {
  my $pat = $endf;
  $pat =~ s/^.//;
  my @f = grep /^[CL]${pat}$/, keys %addr;;  
  if(exists $addr{$endf}) {  
#     print "$endf PAT=$pat|"; print $_ foreach(@f);
    printf ("%-20s : %4d bytes\n",$f[0],$addr{$endf}-$addr{$f[0]});
  }
  
}

exit 0;
