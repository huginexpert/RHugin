.onLoad <- function(libname, pkgname)
{
  sysname <- Sys.info()["sysname"]

  if(sysname == "Windows") {

    HuginVersion <- NULL ###ConfigureHuginVersionHere###
    HuginInst <- NULL ###ConfigureHuginDirHere###
    HuginDllDir <- NULL ###ConfigureHuginDllDirHere###

    if(is.null(HuginDllDir))
      stop("RHugin was not properly configured during installation")

    if(!file.exists(HuginDllDir))
      stop("Hugin Decision Engine (HDE) not found; reinstalling RHugin may fix this problem")

    path <- Sys.getenv("PATH")
    Sys.setenv(PATH = file.path(HuginDllDir, path, fsep = .Platform$path.sep))
    
    cat("\nLoading RHugin package...\n")
    cat("  RHugin package version:",
        as.character(packageVersion("RHugin", lib.loc = libname)),
        "\n")
    cat("  Hugin Version:",
        HuginVersion,
        "\n")
    cat("  Hugin Location:",
        HuginInst,
        "\n\n")
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


