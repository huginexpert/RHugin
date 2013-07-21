.onLoad <- function(libname, pkgname)
{
  if(Sys.info()["sysname"] == "Windows") {

    path <- Sys.getenv("PATH")

    if(length(grep("HDE7.8C", path)) == 0) {

      HuginExpert <- paste(Sys.getenv("ProgramFiles"), "Hugin Expert", sep = "\\")
      HuginFiles <- list.files(HuginExpert, full.names = TRUE, recursive = TRUE)
      HuginDll <- HuginFiles[grep("hugin2-7.8-vc10.dll", HuginFiles, fixed = TRUE)]

      if(!length(HuginDll))
        warning("RHugin could not find Hugin in the usual location")

      else if(length(HuginDll) >= 2) {
        HuginDll <- HuginDll[1]
        warning("multiple Hugin installations found, using: ", HuginDll)
      }

      HuginDllDir <- strsplit(HuginDll, split = "/", fixed = TRUE)[[1]]
      HuginDllDir <- paste(HuginDllDir[-length(HuginDllDir)], collapse = "\\")

      Sys.setenv(PATH = paste(HuginDllDir, path, sep= ";"))
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
      if(file.exists("/usr/local/hugin"))
        Sys.setenv(HUGINHOME = "/usr/local/hugin")

      else {
        warning("RHugin could not find Hugin in the usual location")
      }
    }
  }

  dll <- library.dynam(pkgname, package = pkgname, lib.loc = libname)
  dotCallRoutines <- names(getDLLRegisteredRoutines(dll)[[".Call"]])
  RHuginPkgEnv <- get("env", envir = parent.frame())

  for(routine in dotCallRoutines)
    assign(routine, getNativeSymbolInfo(routine, dll), envir = RHuginPkgEnv)

  invisible()
}


