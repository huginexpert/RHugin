rm(list = ls())
fsep <- .Platform$file.sep #"\\"
compilerID <- "vc10"

heDir <- file.path(Sys.getenv("PROGRAMFILES"), "Hugin Expert", fsep = fsep)
hugins <- strsplit(list.files(heDir), split = " ", fixed = TRUE)

l4 <- sapply(hugins, length) == 4
isHugin <- sapply(hugins, function(u) u[1]) == "Hugin"
hugins <- hugins[l4 & isHugin]

if(!length(hugins))
  stop("Hugin not found in ", heDir)

type <- sapply(hugins, function(u) u[2])
DorR <- type == "Developer" || type == "Researcher"
if(sum(DorR)) {
  hugins <- hugins[DorR]
  type <- hugins[DorR]
}

versions <- as.numeric(sapply(hugins, function(u) u[3]))
latest <- which.max(versions)

hugin <- paste(hugins[[latest]], collapse = " ")
type <- type[latest]
version <- versions[latest]

HuginCHDEDir <- file.path(heDir, hugin, paste("HDE", version, "C", sep = ""), fsep = fsep)
HuginIncludeDir <- file.path(HuginCHDEDir, "Include", fsep = fsep)
dllName <- paste("hugin2", version, compilerID, "x64.dll", sep = "-")
HuginDll <- list.files(HuginCHDEDir, pattern = glob2rx(dllName),
                       recursive = TRUE, full.names = TRUE)
HuginDllDir <- dirname(HuginDll)


#PKG_CPPFLAGS=-DH_DOUBLE -I$(HUGIN_INCLUDE_DIR)
#PKG_LIBS=-L$(HUGIN_LIB_DIR) -lhugin2 -lm -lz -lpthread $(RHUGIN_LIBCRYPT) \
#$(HUGIN_RPATH)

if(dir.exists(d <- file.path("src", "HuginDll")))
  unlink(d, recursive = TRUE)

dir.create(d)
file.copy(HuginDll, file.path(d, dllName))

if(file.exists(m <- file.path("src", "Makevars.win")))
  file.remove(m)

cppflags <- paste("PKG_CPPFLAGS=-DH_DOUBLE -I\"",
                  HuginIncludeDir, "\"", sep = "")
pkglibs <- paste("PKG_LIBS=-L\"", file.path(getwd(), "src", "HuginDll"), "\"",
                 " -l", "\"", substr(dllName, 1, 19), "\" ", "-lm -lz", sep = "")

writeLines(c(cppflags, pkglibs), con = m)

onLoad <- readLines(ol <- file.path("R", "onLoad.q"))
i <- grep("###ConfigureHuginDllDirHere###", onLoad)
onLoad[i] <- paste("    HuginDllDir <- ", "\"", HuginDllDir, "\" ", "###ConfigureHuginDllDirHere###", sep = "")
status <- file.remove(ol)
writeLines(onLoad, con = ol)


