.First.lib <- function(libname, pkgname)
{
  if(Sys.info()["sysname"] == "Windows") {

    path <- Sys.getenv("PATH")

    if(length(grep("HDE7.1C", path)) == 0) {

      HuginVersions <- c("Hugin Researcher 7.1",
                         "Hugin Lite 7.1")

      HuginDllPaths <- paste(Sys.getenv("PROGRAMFILES"),
                            "Hugin Expert",
                             HuginVersions,
                            "HDE7.1C\\Lib\\VC8\\Release\\hugin2-7.1-vc8.dll",
                             sep = "\\")

      if(length(HuginVersion <- which(file.exists(HuginDllPaths)))) {

        HuginVersion <- HuginVersions[HuginVersion[1]]

        HuginPath <- paste(Sys.getenv("PROGRAMFILES"),
                          "Hugin Expert",
                           HuginVersion,
                          "HDE7.1C\\Lib\\VC8\\Release",
                           sep = "\\")

        Sys.setenv(PATH = paste(path, HuginPath, sep= ";"))
      }

      else {
        detach("package:RHugin")
        stop("auto-detection of Hugin failed", "\n",
             "add the folder containing the file ",
              dQuote("hugin2-7.1-vc8.dll"),
             " to the Windows path")
      }
    }
  }

  else if(Sys.info()["sysname"] == "Darwin") {

    if(nchar(Sys.getenv("HUGINHOME")) == 0) {

      HuginVersions <- c("HDE7.1-researcher",
                         "HDE7.1-lite")

      HuginHomes <- paste("/Applications", HuginVersions, sep = "/")

      if(length(HuginVersion <- which(file.exists(HuginHomes)))) {
        HuginHome <- HuginHomes[HuginVersion[1]]
        Sys.setenv(HUGINHOME = HuginHome)
      }

      else {
        detach("package:RHugin")
        stop("auto-detection of Hugin failed", "\n",
             "set the HUGINHOME environment variable (see Hugin Documentation)")
      }
    }
  }

  else {
    if(nchar(Sys.getenv("HUGINHOME")) == 0) {
      if(file.exists("/usr/local/hugin"))
        Sys.setenv(HUGINHOME = "/usr/local/hugin")

      else {
        detach("package:RHugin")
        stop("auto-detection of Hugin failed - ",
             "set the HUGINHOME environment variable")
      }
    }
  }

  library.dynam("RHugin")
  invisible(NULL)
}


