.onLoad <- function(libname, pkgname)
{
  fs <- .Platform$file.sep
  ps <- .Platform$path.sep

  if(Sys.info()["sysname"] == "Windows") {

    path <- Sys.getenv("PATH")
    pv <- packageDescription(pkgname, libname, fields = "Version")
    pv <- strsplit(pv, split = "-", fixed = TRUE)[[1]][1]

    if(!length(grep(paste("HDE", pv, "C", sep = ""), path))) {

      HuginExpert <- paste(Sys.getenv("ProgramFiles"), "Hugin Expert", sep = fs)
      HuginFiles <- list.files(HuginExpert, full.names = TRUE, recursive = TRUE)
      x64 <- ifelse(.Machine$sizeof.pointer == 4, "", "-x64")
      dllName <- paste("hugin2-", pv, "-vc10", x64, ".dll", sep = "")
      HuginDll <- HuginFiles[grep(dllName, HuginFiles, fixed = TRUE)]

      if(!length(HuginDll))
        warning("RHugin ", pv, ": could not find Hugin Expert ", pv)

      else if(length(HuginDll) > 1) {
        HuginDll <- HuginDll[1]
        warning("multiple Hugin installations found, using: ", HuginDll)
      }

      HuginDllDir <- dirname(HuginDll)
      HuginDllDir <- strsplit(HuginDllDir, split = fs, fixed = TRUE)[[1]]
      HuginDllDir <- paste(HuginDllDir, collapse = "\\")

      Sys.setenv(PATH = paste(HuginDllDir, path, sep = ps))
    }
  }

  else if(Sys.info()["sysname"] == "Darwin") {

    if(!nchar(Sys.getenv("HUGINHOME"))) {

      Apps <- list.files("/Applications", full.names = TRUE)
      HuginHome <- Apps[grep("HDE", Apps, fixed = TRUE)]

      if(!length(HuginHome))
        warning("RHugin could not find Hugin in /Applications")

      else if(length(HuginHome) >= 2) {
        HuginHome <- HuginHome[1]
        warning("multiple Hugin installations found, using: ", HuginHome)
      }

      Sys.setenv(HUGINHOME = HuginHome)
    }
  }

  else {
    if(!nchar(Sys.getenv("HUGINHOME"))) {
      ulh <- paste(c(paste(c(fs, "usr"), collapse = ""), "local", "hugin"),
                   collapse = fs)

      if(file.exists(ulh))
        Sys.setenv(HUGINHOME = ulh)
      else
        warning("RHugin did not find Hugin in ", ulh)
    }
  }

  dll <- library.dynam(pkgname, package = pkgname, lib.loc = libname)
  dotCallRoutines <- names(getDLLRegisteredRoutines(dll)[[".Call"]])
  RHuginPkgEnv <- get("env", envir = parent.frame())

  for(routine in dotCallRoutines)
    assign(routine, getNativeSymbolInfo(routine, dll), envir = RHuginPkgEnv)

  invisible()
}


