#!/bin/tcsh -f 

set startnumber=2
set endnumber=8
set runnumber=$startnumber 

while( $runnumber <= $endnumber)
bsub -q s root -l 'errorfit.cc('$runnumber')' 

set runnumber=`expr $runnumber + 1`

end  
