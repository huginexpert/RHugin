.onLoad <- function(libname, pkgname)
{
      HuginDllDir <- "C:/Program Files/Hugin Expert/Hugin Lite 9.1 (x64)/HDE9.1C/Lib/VC10/Release" ###ConfigureHuginDllDirHere###
  
  if(Sys.info()["sysname"] == "Windows") {
      HuginVersion <- "Hugin Lite 9.1 (x64)" ###ConfigureHuginVersionHere###
      HuginInst <- "C:/Program Files/Hugin Expert/Hugin Lite 9.1 (x64)" ###ConfigureHuginDirHere###

    if(is.null(HuginDllDir))
      stop("RHugin was not properly configured during installation")

    if(!file.exists(HuginDllDir))
      stop("Hugin Decision Engine (HDE) not found; reinstalling RHugin may fix this problem")

    m <- "Loading RHugin package..."
    m[2] <- paste("  RHugin package version:",
                  as.character(packageVersion("RHugin", lib.loc = libname)))
    m[3] <- paste("  Hugin Version:", HuginVersion)
    m[4] <- paste("  Hugin Location:", HuginInst)
      
    packageStartupMessage(paste(m, collapse = "\n"))
  }

  # Load the package dll
  dll <- library.dynam(pkgname, package = pkgname, lib.loc = libname,
                       DLLpath = HuginDllDir)
    
  # Inject registered .Call routines into package namespace
  dotCallRoutines <- names(getDLLRegisteredRoutines(dll)[[".Call"]])
  RHuginPkgEnv <- get("env", envir = parent.frame())

  for(routine in dotCallRoutines)
    assign(routine, getNativeSymbolInfo(routine, dll), envir = RHuginPkgEnv)

  invisible()
}


.onUnload <- function(libpath)
{
  dll <- library.dynam.unload("RHugin", libpath = libpath)

  invisible()
}


