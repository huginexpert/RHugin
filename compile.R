# This file can be used to recompile and re-install the package
# if other means do not work properly.

# Restart R-environment: Ctrl + Shift + F10
library(devtools)
# Windows won't release lock on package without this(!?)
cc <- hugin.class.collection()
remove.packages("RHugin") # Ensure package gets removed.
install() # If install failed try running again (usually works).