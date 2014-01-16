if(basename(getwd()) != "Windows" || basename(dirname(getwd())) != "RHugin")
  stop("working directory is not .../RHugin/Windows")

dir.create("i386")
dir.create("x64")

  ## i386 ##

R32 <- paste(Sys.getenv("R_HOME"), "bin", "i386", "R.dll", sep = .Platform$file.sep)
cmd <- paste("dumpbin.exe", "/exports", R32)

dump <- system(cmd, intern = TRUE)


p <- strsplit(dump[15], split = " ", fixed = TRUE)[[1]]
n.funs <- as.numeric((p[nchar(p) > 0])[1])

exports <- strsplit(dump[20:(n.funs + 19)], split = " ", fixed = TRUE)
exports <- sapply(exports, function(u) u[length(u)])
exports <- c("EXPORTS", paste(" ", exports), "")
exports <- paste(exports, collapse = "\n")

cat(exports, file = "i386/R.def")

cwd <- getwd()
setwd("i386")
system("lib /def:R.def /machine:x86")

setwd(cwd)


  ## x64 ##

R64 <- paste(Sys.getenv("R_HOME"), "bin", "x64", "R.dll", sep = .Platform$file.sep)
cmd <- paste("dumpbin.exe", "/exports", R64)

dump <- system(cmd, intern = TRUE)


p <- strsplit(dump[15], split = " ", fixed = TRUE)[[1]]
n.funs <- as.numeric((p[nchar(p) > 0])[1])

exports <- strsplit(dump[20:(n.funs + 19)], split = " ", fixed = TRUE)
exports <- sapply(exports, function(u) u[length(u)])
exports <- c("EXPORTS", paste(" ", exports), "")
exports <- paste(exports, collapse = "\n")

cat(exports, file = "x64/R.def")

cwd <- getwd()
setwd("x64")
system("lib /def:R.def /machine:x64")

setwd(cwd)





