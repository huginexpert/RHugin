.onLoad <- function(libname, pkgname)
{
  sysname <- Sys.info()["sysname"]

  if(sysname == "Windows") {

    path <- Sys.getenv("PATH")
    HuginDll <- NULL

    if(is.null(HuginDll))
      stop("RHugin was not properly configured during installation")

    if(!file.exists(HuginDll))
      stop("Hugin Decision Engine (HDE) not found; reinstalling RHugin may fix this problem")

    HuginDllDir <- strsplit(dirname(HuginDll), split = .Platform$file.sep, fixed = TRUE)[[1]]
    HuginDllDir <- paste(HuginDllDir, collapse = "\\")

    Sys.setenv(PATH = file.path(HuginDllDir, path, fsep = .Platform$path.sep))
  }

  else if(sysname == "Darwin") {

    if(!nchar(Sys.getenv("HUGINHOME"))) {

      Apps <- list.files("/Applications", full.names = TRUE)
      HuginHome <- Apps[grep("HDE", Apps, fixed = TRUE)]

      if(!length(HuginHome))
        stop("RHugin did not find Hugin in /Applications")

      else if(length(HuginHome) >= 2) {
        HuginHome <- HuginHome[1]
        warning("multiple Hugin installations found, using: ", HuginHome)
      }

      Sys.setenv(HUGINHOME = HuginHome)
    }
  }

  else {
    if(!nchar(Sys.getenv("HUGINHOME"))) {

      if(file.exists(ulh <- file.path("usr", "local", "hugin")))
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


