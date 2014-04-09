.onLoad <- function(libname, pkgname)
{
  fs <- .Platform$file.sep
  ps <- .Platform$path.sep

  if(Sys.info()["sysname"] == "Windows") {

    path <- Sys.getenv("PATH")

    if(length(grep("HDE8.0C", path)) == 0) {

      HuginExpert <- paste(Sys.getenv("ProgramFiles"), "Hugin Expert", sep = fs)
      HuginFiles <- list.files(HuginExpert, full.names = TRUE, recursive = TRUE)

      dllName <- ifelse(.Machine$sizeof.pointer == 4,
                        "hugin2-8.0-vc10d.dll",
                        "hugin2-8.0-vc10d-x64.dll")

      HuginDll <- HuginFiles[grep(dllName, HuginFiles, fixed = TRUE)]

      if(!length(HuginDll))
        warning("RHugin could not find the Hugin dll")

      else if(length(HuginDll) >= 2) {
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

    if(nchar(Sys.getenv("HUGINHOME")) == 0) {

      Apps <- list.files("/Applications", full.names = TRUE)
      HuginHome <- Apps[grep("HDE", Apps, fixed = TRUE)]

      if(!length(HuginHome))
        warning("RHugin could not find Hugin in the usual location")

      else if(length(HuginHome) >= 2) {
        HuginHome <- HuginHome[1]
        warning("multiple Hugin installations found, using: ", HuginHome)
      }

      Sys.setenv(HUGINHOME = HuginHome)
    }
  }

  else {
    if(nchar(Sys.getenv("HUGINHOME")) == 0) {
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


