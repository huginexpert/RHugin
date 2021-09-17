rm(list = ls())
library(tools)

compilerID <- "vc10"

if(nchar(hugins <- Sys.getenv("RHUGIN_HUGINHOME"))) {
  HEDir <- dirname(hugins)
  hugins <- basename(hugins)
} else {
  HEDir <- file.path(Sys.getenv("PROGRAMFILES"), "Hugin Expert")
  HEDir <- file.path(dirname(HEDir), basename(HEDir))
  hugins <- list.files(HEDir)
}

hugins <- strsplit(hugins, split = " ", fixed = TRUE)
l4 <- sapply(hugins, length) == 3
isHugin <- sapply(hugins, function(u) u[1]) == "HUGIN"
hugins <- hugins[l4 & isHugin]

if(!length(hugins))
  stop("Hugin not found in ", HEDir)

types <- sapply(hugins, function(u) u[2])
DorR <- types == "Developer" || types == "Researcher"
if(sum(DorR)) {
  hugins <- hugins[DorR]
  types <- types[DorR]
}
versions <- (sapply(hugins, function(u) u[2])) #OBS Change u[2] to u[3] if hugin is not found
#versions <- as.numeric(sapply(hugins, function(u) u[2])) #OBS Change u[2] to u[3] if hugin is not found
latest <- which.max(versions)

hugin <- paste(hugins[[latest]], collapse = " ")
type <- types[latest]
version <- versions[latest]
HuginCHDEDir <- file.path(HEDir, hugin, paste("HDE", version, "C", sep = ""))
HuginIncludeDir <- file.path(HuginCHDEDir, "Include")
dllName <- paste("hugin2", version, compilerID, "x64.dll", sep = "-")
HuginDll <- list.files(HuginCHDEDir, pattern = glob2rx(dllName),
                       recursive = TRUE, full.names = TRUE)
HuginDllDir <- dirname(HuginDll)

if(dir.exists(d <- file.path("src", "HuginDll")))
  status <- unlink(d, recursive = TRUE)

status <- dir.create(d)
status <- file.copy(HuginDll, file.path(d, dllName))

if(file.exists(m <- file.path("src", "Makevars.win")))
  status <- file.remove(m)

cppflags <- paste("PKG_CPPFLAGS=-DH_DOUBLE -I\"",
                  HuginIncludeDir, "\"", sep = "")
pkglibs <- paste("PKG_LIBS=-L\"", file.path(getwd(), "src", "HuginDll"), "\"",
                 " -l", "\"", file_path_sans_ext(dllName), "\" ", "-lm -lz",
                 sep = "")

writeLines(c(cppflags, pkglibs), con = m)

zzz <- readLines(f <- file.path("R", "zzz.R"))

i <- grep("###ConfigureHuginVersionHere###", zzz)[1]
zzz[i] <- paste("      HuginVersion <- ",
                   "\"",
                   hugin,
                   "\"",
                   " ###ConfigureHuginVersionHere###",
                   sep = "")

i <- grep("###ConfigureHuginDirHere###", zzz)[1]
zzz[i] <- paste("      HuginInst <- ",
                   "\"",
                   file.path(HEDir, hugin),
                   "\" ",
                   "###ConfigureHuginDirHere###",
                   sep = "")

i <- grep("###ConfigureHuginDllDirHere###", zzz)[1]
zzz[i] <- paste("      HuginDllDir <- ",
                   "\"",
                   HuginDllDir,
                   "\" ",
                   "###ConfigureHuginDllDirHere###",
                   sep = "")

status <- file.remove(f)
writeLines(zzz, con = f)


