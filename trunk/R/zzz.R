.onLoad <- function(libname, pkgname)
{
      HuginDllDir <- NULL ###ConfigureHuginDllDirHere###
  
  if(Sys.info()["sysname"] == "Windows") {
      HuginVersion <- NULL ###ConfigureHuginVersionHere###
      HuginInst <- NULL ###ConfigureHuginDirHere###

    if(is.null(HuginDllDir))
      stop("RHugin was not properly configured during installation")

    if(!file.exists(HuginDllDir))
      stop("Hugin Decision Engine (HDE) not found; reinstalling RHugin may fix this problem")

    packageStartupMessage("Loading RHugin package...")
    packageStartupMessage("  RHugin package version: ",
                          as.character(packageVersion("RHugin", lib.loc = libname)))
    packageStartupMessage("  Hugin Version: ", HuginVersion)
    packageStartupMessage("  Hugin Location: ", HuginInst)
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


