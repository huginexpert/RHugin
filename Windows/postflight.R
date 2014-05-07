if(basename(getwd()) != "Windows" || basename(dirname(getwd())) != "RHugin")
  stop("working directory is not .../RHugin/Windows")

if(file.exists("../inst/libs")) unlink("../inst/libs", recursive = TRUE, force = TRUE)

tmp <- dir.create("../inst/libs")
tmp <- dir.create("../inst/libs/i386")
tmp <- dir.create("../inst/libs/x64")

msvcr <- "C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/redist/x86/Microsoft.VC100.CRT/msvcr100.dll"
tmp <- file.copy(msvcr, "../inst/libs/i386/msvcr100.dll")
tmp <- file.copy("i386/RHugin.dll", "../inst/libs/i386/RHugin.dll")

msvcr <- "C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/redist/x64/Microsoft.VC100.CRT/msvcr100.dll"
tmp <- file.copy(msvcr, "../inst/libs/x64/msvcr100.dll")
tmp <- file.copy("x64/RHugin.dll", "../inst/libs/x64/RHugin.dll")


if(file.exists("../src")) tmp <- file.rename("../src", "../HIDE-src")

description <- readLines("../DESCRIPTION")
os.type <- which(substring(description, 1, 7) == "OS_type")
description[os.type] <- "OS_type: windows"
tmp <- file.remove("../DESCRIPTION")
tmp <- writeLines(description, "../DESCRIPTION")



