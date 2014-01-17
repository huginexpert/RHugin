if(basename(getwd()) != "Windows" || basename(dirname(getwd())) != "RHugin")
  stop("working directory is not .../RHugin/Windows")

fs <- .Platform$file.sep

if(!file.exists("../inst/libs")) dir.create("../inst/libs")
if(!file.exists("../inst/libs/i386")) dir.create("../inst/libs/i386")
if(!file.exists("../inst/libs/x64")) dir.create("../inst/libs/x64")

redist.i386 <- c("msvcp110.dll", "msvcr110.dll", "vccorlib110.dll")
for(f in redist.i386)
  file.copy(paste("redist-i386", f, sep = fs), paste("../inst/libs/i386", f, sep = fs))
file.copy("../i386/Release/RHugin.dll", "../inst/libs/i386/RHugin.dll")

redist.x64 <- c("msvcp110.dll", "msvcr110.dll", "vccorlib110.dll")
for(f in redist.x64)
  file.copy(paste("redist-x64", f, sep = fs), paste("../inst/libs/x64", f, sep = fs))
file.copy("../x64/Release/RHugin.dll", "../inst/libs/x64/RHugin.dll")

if(file.exists("../src")) file.rename("../src", "../HIDE-src")


