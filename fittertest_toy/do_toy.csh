#!/bin/tcsh -f 

set startnumber=1
set endnumber=1000
set runnumber=$startnumber 

while( $runnumber <= $endnumber)
bsub -q s root -l 'roofit_toytest2.cc('$runnumber')' 

set runnumber=`expr $runnumber + 1`

end  
