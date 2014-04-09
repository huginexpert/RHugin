if(basename(getwd()) != "Windows" || basename(dirname(getwd())) != "RHugin")
  stop("working directory is not .../RHugin/Windows")

arch <- commandArgs(TRUE)[1]
arch <- match.arg(arch, c("x86", "x64"))

Rarch <- switch(arch,
  "x86" = "i386",
  "x64" = "x64",
  stop("architecture not recognized")
)

if(file.exists(Rarch)) unlink(Rarch, recursive = TRUE, force = TRUE)
dir.create(Rarch)

fs <- .Platform$file.sep

R <- paste(Sys.getenv("R_HOME"), "bin", Rarch, "R.dll", sep = fs)
cmd <- paste("dumpbin.exe", "/exports", R)

dump <- system(cmd, intern = TRUE)
p <- strsplit(dump[15], split = " ", fixed = TRUE)[[1]]
n.funs <- as.numeric((p[nchar(p) > 0])[1])

exports <- strsplit(dump[20:(n.funs + 19)], split = " ", fixed = TRUE)
exports <- sapply(exports, function(u) u[length(u)])
exports <- c("EXPORTS", paste(" ", exports), "")
exports <- paste(exports, collapse = "\n")

cat(exports, file = paste(Rarch, "R.def", sep = fs))

cwd <- getwd()
setwd(Rarch)
system(paste("lib /def:R.def /machine:", arch, sep = ""))
setwd(cwd)

