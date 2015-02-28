#!/usr/bin/perl

use strict;

##############################################################################
#
#  recursively scan source files (passed on command line) for local include 
#  files and save these in Makefile.extra_includes
#
##############################################################################

my @headers = ();

foreach my $f (@ARGV) {
  &scanFile($f);
}

@headers = sort @headers;
foreach (@headers) {
  print $_," ";
}
print "\n";

exit 0;

sub scanFile
{
  my $f = shift;
  open (my $IN, "<", "$f") or die "Could not open $f: $!";
  while(<$IN>) {
    if(/^#include +\"([^\"]+)\"/) {
      if (!(grep {$_ eq $1} @headers)) { # modern would be:  if($1 ~~ @headers) {
	push @headers,$1;
	&scanFile($1);
      }
    }
  }
  close $IN;
}
