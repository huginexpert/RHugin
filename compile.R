# This file can be used to recompile and re-install the package
# (run one command at a time (and do it slowly))

# Restart R-environment: Ctrl + Shift + F10
library(devtools)
# Windows won't release lock on package binaries without this
cc <- hugin.class.collection()
# Ensure earlier version package gets removed.
remove.packages("RHugin") 
install() 
install() # Sometimes first time does not work so try again.

