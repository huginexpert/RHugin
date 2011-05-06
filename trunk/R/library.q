.First.lib <- function(libname, pkgname)
{
  if(Sys.info()["sysname"] == "Windows") {

    path <- Sys.getenv("PATH")

    if(length(grep("HDE7.4C", path)) == 0) {

      HuginVersions <- c("Hugin Researcher 7.4",
                         "Hugin Lite 7.4")

      HuginDllPaths <- paste(Sys.getenv("PROGRAMFILES"),
                            "Hugin Expert",
                             HuginVersions,
                            "HDE7.4C\\Lib\\VC8\\Release\\hugin2-7.4-vc8.dll",
                             sep = "\\")

      if(length(HuginVersion <- which(file.exists(HuginDllPaths)))) {

        HuginVersion <- HuginVersions[HuginVersion[1]]

        HuginPath <- paste(Sys.getenv("PROGRAMFILES"),
                          "Hugin Expert",
                           HuginVersion,
                          "HDE7.4C\\Lib\\VC8\\Release",
                           sep = "\\")

        Sys.setenv(PATH = paste(path, HuginPath, sep= ";"))
      }

      else {
        warning("RHugin did not find Hugin in the expected location")
      }
    }
  }

  library.dynam("RHugin")
  invisible(NULL)
}


