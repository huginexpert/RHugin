if(basename(getwd()) != "Windows" || basename(dirname(getwd())) != "RHugin")
  stop("working directory is not .../RHugin/Windows")

fs <- .Platform$file.sep

if(!file.exists("../inst/libs")) tmp <- dir.create("../inst/libs")
if(!file.exists("../inst/libs/i386")) tmp <- dir.create("../inst/libs/i386")
if(!file.exists("../inst/libs/x64")) tmp <- dir.create("../inst/libs/x64")

redist.i386 <- c("msvcp100.dll", "msvcr100.dll")
for(f in redist.i386)
  tmp <- file.copy(paste("redist-i386", f, sep = fs), paste("../inst/libs/i386", f, sep = fs))
tmp <- file.copy("RHuginVS2010E/Win32/Release/RHugin.dll", "../inst/libs/i386/RHugin.dll")

redist.x64 <- c("msvcp100.dll", "msvcr100.dll")
for(f in redist.x64)
  tmp <- file.copy(paste("redist-x64", f, sep = fs), paste("../inst/libs/x64", f, sep = fs))
tmp <- file.copy("RHuginVS2010E/x64/Release/RHugin.dll", "../inst/libs/x64/RHugin.dll")

if(file.exists("../src")) tmp <- file.rename("../src", "../HIDE-src")

description <- readLines("../DESCRIPTION")
os.type <- which(substring(description, 1, 7) == "OS_type")
description[os.type] <- "OS_type: windows"
tmp <- file.remove("../DESCRIPTION")
tmp <- writeLines(description, "../DESCRIPTION")



